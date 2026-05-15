using Combinatorics

function partitions_fixed(n, k)
    """
    Generate all partitions of the set {1, 2, ..., n} into exactly k subsets.

    Args:
        n::Int: The number up to which partitions are generated.
        k::Int: The desired number of subsets in each partition.

    Returns:
        Vector{Vector{Vector{Int}}}: A list of partitions, each with k subsets.
    """
    if k == 0
        return n == 0 ? [[]] : []  # Only an empty partition if n == 0
    elseif n == 0
        return []
    end

    prev_partitions = partitions_fixed(n - 1, k)
    result = []

    # Add `n` to an existing subset if there are `k` subsets
    for partition in prev_partitions
        for i in 1:length(partition)
            new_partition = deepcopy(partition)
            push!(new_partition[i], n)
            push!(result, new_partition)
        end
    end

    # Add `n` as a new subset if there are fewer than `k` subsets
    smaller_partitions = partitions_fixed(n - 1, k - 1)
    for partition in smaller_partitions
        new_partition = deepcopy(partition)
        push!(new_partition, [n])
        push!(result, new_partition)
    end

    return result
end

function generate_tests(n::Int)
    sets = Vector{Vector{Int64}}()
    for k in 1:n
        for subset in combinations(1:n, k)
            push!(sets, subset)
        end
    end
    return sets
end
