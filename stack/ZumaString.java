import java.util.Stack;

/*
 连续相同的字符串消除掉，效果跟祖玛类似
 */
public class Main {
    public static void main(String[] args) {
        String str = "180008935531";
        
        Stack<Character> stack = new Stack<>();
        stack.push(str.charAt(0));
        
        int l = str.length();
        int i = 1;
        int j;
        
        while (i < str.length()) {
            char c = str.charAt(i);
            if (stack.peek() == c) {//如果碰到与栈顶相同的char，跳过后续所有相同的char，并且出栈栈顶char
                j = i + 1;
                while (j < l && str.charAt(j) == c) {//跳过所有相同的，如18000的后一个0
                    j++;
                }
                i = j;
                stack.pop();//出栈
            } else {//不同，入栈
                stack.push(c);
                i++;
            }
        }
        
        str = "";
        for (i = 0; i < stack.size(); i++) {
            str += stack.get(i);
        }
        
        System.out.println(str);
    }
}
