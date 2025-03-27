
def merge_sort(arr):
    def _merge(arr, l, m, r):
        buff = []
        i = l
        j = m + 1
        while i <= m and j <= r:
            if arr[i] <= arr[j]:
               buff.append(arr[i])
               i+=1
            else:
                buff.append(arr[j])
                j+=1
        while j <= r:
            buff.append(arr[j])
            j+=1
            
        while i <= m:
            buff.append(arr[i])
            i+=1
        
        arr[l:r+1] = buff[:]
       

    def _merge_sort(arr, a, b):
        if a >= b:
            return
        m = (a + b)//2
        _merge_sort(arr, a, m)
        _merge_sort(arr, m+1, b)
        _merge(arr, a, m, b)

    _merge_sort(arr, 0, len(arr)-1)

def test_sorter(sorter):
    import random
    def create_arr():
        arr = []
        len = random.randrange(1, 1000)
        for _ in range(len):
            arr.append(random.randrange(-99, 100))
        return arr
    # for i in range(100):
        # arr = create_arr()
        # carr = arr[:]
        # sorter(carr)
        # arr.sort()
        # assert(arr == carr)
    def big():
        s  = 100000
        e = [random.randrange(-999,2000) for i in range(s)]
        ce = sorted(e)
        sorter(e)
        assert(e == ce)
    big()



test_sorter(merge_sort)
