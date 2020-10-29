// container.c

inherit ITEM;

int is_container() { return 1; }

string extra_long()
{
        string str;

        str  = sprintf("\n物品属性 : 容器，下线%s丢失\n", 
                       (this_object()->query_autoload() || query("autoload")) ? "不" : "" );      
        str += sprintf("容    量 : %d\n", this_object()->query_max_encumbrance());
        str += sprintf("限    制 : %s\n", this_object()->no_limit_amount() ? "否" : "是");
        //str += sprintf("使用方法 : 输入指令 put <id> in %s 放入。\n", query("id"));
        //str += sprintf("                  输入指令 get <id> from %s 取出。\n", query("id"));

        return str;
}
