# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
from heapq import heappush, heappop, heapify 

class Solution:
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        heap = []
        
        for idx, ll in enumerate(lists):
            if ll:                             
                heappush(heap, (ll.val, idx))
                lists[idx] = ll.next
        res = []
        while len(heap) > 0:
            val, idx = heappop(heap) 
            res.append(val)
            if lists[idx] != None:
                heappush(heap, (ll.val, idx))
                lists[idx] = lists[idx].next

        return res
