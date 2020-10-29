// food.c

#include <name.h>

//string short() { return name() + "(" + capitalize(query("id")) + ")"; }

mixed func = 0;
int is_food() { return 1; }

void apply_effect(function f)
{
        if( !func )
                func = f;
        else if( functionp(func) )
                func = ({ func, f });
        else if( sizeof(func) < 12 )
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
                for( i=0; i < sizeof(func); i++ )
                        evaluate(func[i]);
}

string extra_long()
{
        string str;

        str =  "物品类型    ：    食物\n";
        str += sprintf("重    量    ：    %d\n", this_object()->query_weight());
        str += sprintf("能    量    ：    %d\n", query("food_supply"));
        str += sprintf("剩    余    ：    %d\n", query("food_remaining"));
        str += sprintf("使用方式    ：    输入指令 eat %s 食用。\n", query("id"));
        if( this_object()->query_autoload() )
                str += "下线丢失    ：    否\n";
        else
                str += "下线丢失    ：    是\n";
        return str;
}

int feed_ob(object me)
{
        string str;
        if( me->is_busy() )
                return notify_fail("你上一个动作还没有完成。\n");
        if( !living(me) ) return 0;

        if( stringp(query("food_race")) )
                return notify_fail( "这可不是给人吃的东西！\n");

        if( !query("food_remaining") )
                return notify_fail( name() + "已经没什么好吃的了。\n");
        if( (int)query("food", me) >= (int)me->max_food_capacity() )
                return notify_fail("你已经吃太饱了，再也塞不下任何东西了。\n");

        addn("food", query("food_supply"), me);

        addn("jingli", query("food_supply")/5, me);
        if( query("jingli", me) > query("max_jingli", me))
                set("jingli", query("max_jingli",me), me);

        if( me->is_fighting() ) me->start_busy(2);

        // This allows customization of drinking effect.
        if( query("eat_func") ) return 1;

        set("value", 0);
        addn("food_remaining", -1);
        if( !query("food_remaining") ) {
                if( !stringp(str = query("eat_all")) )
                str = "$N将剩下的$n吃得乾乾净净。\n";
                message_vision(str, this_player(),this_object());
                if( !this_object()->finish_eat() )
                        destruct(this_object());
        } else  {
                if( !stringp(str = query("eat_msg")) )
                str = "$N拿起$n咬了几口。\n";
                message_vision(str, this_player(),this_object());
        }
        //me->start_busy(1);
        return 1;
}

void init()
{
        if( !query("decay") && userp(environment()) ) {
                set("decay", 1);
                remove_call_out("decay");
                call_out("decay", 280);
        }
}

void decay()
{
        object me = this_object(), ob = environment();
        if( !me || !ob ) return;
        switch(addn("decay", 1))
        {
                case 2:
                        set_temp("apply/long",({query("long")+"可是看起来不是很新鲜。\n"}));
                        tell_object(ob, me->name()+"的颜色有些不对了。\n");
                        break;
                case 3:
                        set_temp("apply/long", ({query("long")+"可是正在散发出一股难闻的味道。\n"}));
                        tell_object(ob,me->name()+"散发出一股难闻的味道。\n");
                        break;
                case 4:
                        set_temp("apply/long",({query("long")+"可是有些腐烂了。\n"}));
                        tell_object(ob,me->name()+"有些腐烂了，发出刺鼻的味道。\n");
                        break;
                default:
                        tell_object(ob,me->name()+"整个腐烂掉了。\n");
                        destruct(this_object());
                        return;
        }
        remove_call_out("decay");
        call_out("decay", 150);
}