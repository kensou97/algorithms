c class Solution {
   public boolean searchMatrix(int[][] matrix, int target) {
        int rows = matrix.length;
        if (rows == 0) {
            return false;
        }
        int cols = matrix[0].length;
        if (cols == 0) {
            return false;
        }


        return search(matrix, 0, rows - 1, rows - 1, 0, cols - 1, cols - 1, target);
    }

    private boolean search(int[][] matrix, int r0, int r1, int r, int c0, int c1, int c, int target) {
        //终止情况 or 越界
        if (r0 > r1 || c0 > c1 || r0 < 0 || c0 < 0 || r1 > r || c1 > c) {
            return false;
        }

        if (r0 == r1 && c0 == c1) {
            return target == matrix[r0][c0];
        }

        int middle_r = (r0 + r1) / 2;
        int middle_c = (c0 + c1) / 2;

        int middle = matrix[middle_r][middle_c];
        //恰好找到
        if (middle == target) {
            return true;
        }

        //比目标大，排除右下角
        if (middle > target) {
            return search(matrix, r0, middle_r - 1, r, c0, middle_c - 1, c, target)/*左上角*/
                    || search(matrix, r0, middle_r - 1, r, middle_c, c1, c, target)/*右上角带左边界*/
                    || search(matrix, middle_r, r1, r, c0, middle_c - 1, c, target);/*左下角带上边界*/
        }

        //比目标小，排除左上角
        return search(matrix, middle_r + 1, r1, r, middle_c + 1, c1, c, target)/*右下角*/
                || search(matrix, r0, middle_r, r, middle_c + 1, c1, c, target)/*右上角带下边界*/
                || search(matrix, middle_r + 1, r1, r, c0, middle_c, c, target);/*左下角带右边界*/
    }
}
