import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.Map;

/*
frequency node:
     _______________                 _______________
    |               |     next      |               |
    | frequency=1   | ----------->  | frequency=3   |
    | keys:{3.2}    |               | keys:{1,4,5}  |
    |               | <-----------  |               |
    |_______________|     prev      |_______________|
 */

public class LFUCache {

    private Map<Integer, Integer> valueMap;
    private Map<Integer, Node> frequencyMap;
    private int capacity;
    private Node head;

    public LFUCache(int capacity) {
        valueMap = new HashMap<>(capacity);
        frequencyMap = new HashMap<>();
        this.capacity = capacity;
        head = new Node();
        head.frequency = -1;
    }

    public int get(int key) {
        Integer i = valueMap.get(key);
        if (i == null) {
            System.out.println(-1);
            return -1;
        }
        incrementFrequency(key);
        System.out.println(i);
        return i;
    }

    private void incrementFrequency(int key) {
        Node node = frequencyMap.get(key);//node is never null
        Node prev;
        Node next = node.next;
        if (next == null || next.frequency != node.frequency + 1) {
            Node tmp = new Node();
            tmp.frequency = node.frequency + 1;
            tmp.prev = node;
            tmp.next = next;

            node.next = tmp;
            if (next != null) {
                next.prev = tmp;
            }

            next = tmp;
        }

        node.removeKey(key);
        next.addKey(key);
        frequencyMap.put(key, next);

        if (node.keys.size() == 0 && node.frequency != -1) {//need to remove the node because it is empty
            removeFrequencyNode(node);
        }
    }

    private void removeFrequencyNode(Node node) {
        Node prev = node.prev;//node must have prev node because head is never changed or removed
        Node next = node.next;//next may be null

        node.prev = null;
        node.next = null;

        prev.next = next;
        if (next != null) {
            next.prev = prev;
        }
    }

    public void set(int key, int value) {
        if (capacity == 0) {
            return;
        }
        if (valueMap.containsKey(key)) {
            valueMap.put(key, value);
            incrementFrequency(key);
            return;
        }
        if (valueMap.size() == capacity) {
            Node evictNode = head.next;
            Integer last = evictNode.keys.iterator().next();
            if (evictNode.keys.size() == 0 && evictNode.frequency != -1) {//need to remove the node because it is empty
                removeFrequencyNode(evictNode);
            }
//            System.out.println("remove " + last);
            evictNode.keys.remove(last);
            valueMap.remove(last);
            frequencyMap.remove(last);
        }

        valueMap.put(key, value);
        frequencyMap.put(key, head);
        head.addKey(key);
        incrementFrequency(key);
    }


    static class Node {
        Node prev;
        Node next;
        int frequency;
        LinkedHashSet<Integer> keys;

        Node() {
            keys = new LinkedHashSet<Integer>();
        }

        void addKey(Integer key) {
            keys.add(key);
        }

        void removeKey(Integer key) {
            keys.remove(key);
        }
    }
}
