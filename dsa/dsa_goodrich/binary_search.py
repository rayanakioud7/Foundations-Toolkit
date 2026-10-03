def binary_search(data, target, low, high):
    """Return True if target is found in indicated portion of a Python list.

    The search only considers the portion from data[low] to data[high] inclusive.
    """
    if low > high:
        return False                        # interval is empty; no match
    else:
        mid = (low + high) // 2
        if target == data[mid]:
            return True                     # found a match
        elif target < data[mid]:
            return binary_search(data, target, low, mid - 1)
        else:
            return binary_search(data, target, mid + 1, high)

if __name__ == '__main__':
    mlist = [2,3,5,4,7,6,9]
    sortedlist = sorted(mlist)
    print(binary_search(sortedlist, 7, 0, len(sortedlist)-1))