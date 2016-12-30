public class bst_serialize {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if (root == null) {
            return "";
        }
        StringBuilder sb = new StringBuilder();
        preOrder(root, sb);
        return sb.toString();
    }

    public void preOrder(TreeNode node, StringBuilder sb) {
        sb.append(node.val + " ");
        if (node.left != null) {
            preOrder(node.left, sb);
        }
        if (node.right != null) {
            preOrder(node.right, sb);
        }
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if (data == null || data.equals("")) {
            return null;
        }

        String strs[] = data.split(" ");
        int[] nodes = new int[strs.length];
        for (int i = 0; i < strs.length; i++) {
            nodes[i] = Integer.parseInt(strs[i]);
        }
        return recover(nodes, 0, nodes.length - 1);
    }

    public TreeNode recover(int[] nodes, int left, int right) {
        if (left > right) {
            return null;
        }
        if (left == right) {
            return new TreeNode(nodes[left]);
        }
        int rootVal = nodes[left];
        TreeNode root = new TreeNode(rootVal);
        int i = left + 1;
        while (i < nodes.length && nodes[i] < rootVal) {
            i++;
        }
        root.left = recover(nodes, left + 1, i - 1);
        root.right = recover(nodes, i, right);
        return root;
    }

    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }
}