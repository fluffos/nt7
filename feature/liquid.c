// liquid.c

#include <name.h>

mixed func = 0;
int is_liquid(){ return 1; }

void apply_effect(function f)
{
        if( !func )
                func = f;
        else
        if( functionp(func) )
                func = ({ func, f });
        else
        if( sizeof(func) < 12 )
                func += ({ f });
}

void clear_effect()
{
        func = 0;
}

mixed query_effect()
{
        return func;
}

void do_effect()
{
        int i;

        if( functionp(func) )
                evaluate(func);
        if( arrayp(func) )
                for( i = 0; i < sizeof(func); i++ )
                        evaluate(func[i]);
}

string extra_long()
{
        int amount, max;
        string str = "";

        if( amount = query("liquid/remaining") ) {
                max = query("max_liquid");
                if( amount == max )
                        str = "里面装满了" + query("liquid/name") + "。\n";
                else if( amount >= max * 2 / 3 )
                        str = "里面装了七、八分满的" + query("liquid/name") + "。\n";
                else if( amount >= max * 2 / 5 )
                        str = "里面装了五、六分满的" + query("liquid/name") + "。\n";
                else if( amount >= 1 )
                        str = "里面装了少许的" + query("liquid/name") + "。\n";
        }

        str += "物品类型    ：    容器\n";
        str += sprintf("属    性    ：    %s\n", query("liquid/name"));
        str += sprintf("重    量    ：    %d\n", this_object()->query_weight());
        str += sprintf("能    量    ：    %d\n", query("max_liquid"));
        str += sprintf("剩    余    ：    %d\n", query("liquid/remaining"));
        str += sprintf("使用方式    ：    输入指令 drink %s 饮用。\n", query("id"));
        if( this_object()->query_autoload() )
                str += "下线丢失    ：    否\n";
        else
                str += "下线丢失    ：    是\n";
        return str;
}
