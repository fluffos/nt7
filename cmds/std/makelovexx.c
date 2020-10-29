// makelove.c
// updated by Lonely

#include <ansi.h>
#include <command.h>

void do_makelove(object me, object target);
string *loving_msg = ({ 
        HIR "$N轻柔的吻者$n的唇，手掌开始不安分的抚摸$n光滑如缎子般的肌肤，$n娇喘吁吁，双手主动的抱住$N...\n" NOR,
        WHT "$N也越来越兴奋，终于和$n结为一体，只听$n如蚊子般的“恩。。”了一声，似是痛苦，似是舒服...\n" NOR,
        HIW "$N的动作越来越快，越来越猛，$n则配合着$N的节奏释放出对$N的爱，阵阵呻吟,春光熠熠，春潮绵绵...\n" NOR,
        HIM "汹涌澎湃的高潮过后，$n温顺的躺在$N的怀里，听着$N的心跳声，$N轻轻的抚弄着$n光滑的皮肤，无限温柔...\n" NOR,
});

void do_loving(object me, object target, int n);        
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string no_tell, can_tell;
        object target, *ob;
        object where = environment(me);
        int i;

        seteuid(getuid());

/*
        if( !(query("sleep_room", where) )
              || (query("no_sleep_room", where)) )
                return notify_fail("这里做爱可不太好，找个安全点的地方吧！\n");
*/

        if (! arg || ! objectp(target = present(arg, where)))
                return notify_fail("你想和谁做爱？\n");

        if( !target->is_character() || query("not_living", target) )
                return notify_fail("看清楚了，那不是活人！\n");

        if( !query("can_speak", target) )
                return notify_fail("你疯了？想和" + target->name() + "性交？\n");

        if (me == target)
                return notify_fail("你自己要和自己...你还是快回家自己研究吧。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("边动手边做爱？你果然很有创意！\n");


        if( query("gender", me) == "无性" )
                return notify_fail("你这人都这模样了还有兴致？真是少见。\n");

        if( query("gender", me) == query("gender", target) )
                return notify_fail("同性恋么...还是自己好好研究怎么弄吧，这条指令不太合适。\n");

        if( query("age", me)<16 )
                return notify_fail("你还没有发育完全，就想这事？\n");

        if (me->query_condition("huaiyun") > 0 ||
            target->query_condition("huaiyun") > 0)
                return notify_fail("搞笑啊？孕妇要注意宝宝安全，怎么能这样？忍一忍拉！\n");
                
        if( query_temp("pending/makelove", me) == target )
                return notify_fail("你已经向别人提出要求了，可是人家还没有答应你。\n");

        if( query("jing", me)*100/query("max_jing", me)<80 )
                return notify_fail("你的精神不济，现在没有力气和人家做爱。\n");

        if( query("qi", me)*100/query("max_qi", me)<60 )
                return notify_fail("你的体力不支，现在没有力气和人家做爱。\n");

/*
        if( query("gender", me) == "男性" && 
            time()-query_temp("last_makelove", me)<120 )
                return notify_fail("你现在是有心无力，没法再来一次。\n");
*/

/*
        no_tell=query("env/no_tell", target);
        if (no_tell == "all" || no_tell == "ALL" ||
            is_sub(query("id", me),no_tell) )
        {
                can_tell=query("env/can_tell", target);
                if( !is_sub(query("id", me),can_tell) )
                        return notify_fail("这个人不想听你罗嗦啦。\n");
        }

        ob = all_inventory(where);
        for (i = 0; i < sizeof(ob); i++)
                if (ob[i]->is_character() && ob[i] != me &&
                    ob[i] != target && ! wizardp(ob[i]))
                        return notify_fail("这儿还有别人呢，多不好意思呀！\n");
                        
*/
        if( query_temp("pending/makelove", target) == me )
        {
                delete_temp("pending/makelove", target);
                if( query("gender", me) == "男性" )
                        message_sort(YEL "$N过了好半响，实在受不了$n的挑逗突然一把将$n紧紧抱住压在床上....\n" NOR,
                                     me, target);

                else
                        message_sort(YEL "$N极力的忍受着$n火热的挑逗，心头小鹿撞击不停，终于瘫软在$n的怀里，"
                                     "被$n一把横抱了起来，轻柔的放在床上....\n" NOR, me, target);
                            
                do_makelove(me, target);
                return 1;
        }

        set_temp("pending/makelove", target, me);

        message("vision", me->name() + "悄悄的和" + target->name() + "说了几句话。\n",
                environment(me), ({ me, target }));
                
        if( query("gender", me) == "男性" )
        {
                message_sort(YEL "$N轻轻的注视着$n，双手搂在$n的小蛮腰，轻柔的吻着$n的小耳垂....\n" NOR, 
                             me, target);
                me->force_me("tell"+query("id", target)+
                             " 好宝贝，今天就和我欢乐一次吧。");
        } else
        {
                message_sort(YEL "$N的小脸儿红扑扑的，缠上来勾住$n的脖子，胸前紧紧的贴着$n的胸膛，"
                             "小嘴嘟嘟的凑上来轻轻的吻着$n的嘴唇....\n" NOR, me, target);                
                me->force_me("tell"+query("id", target)+
                            " 你现在想要我么？");
        }

        return 1;
}

void do_makelove(object me, object target)
{
        mapping armor;
        string msg;
        string msg1, msg2;
        object man, woman;        

        if( query("gender", me) == "男性" )
        {
                man = me;
                woman = target;
        } else
        {
                man = target;
                woman = me;
        }
        
        message_vision(HIB "...屋里的" + HIR "红烛" + HIB "被吹灭了...\n" NOR, me, target);
        
        msg = YEL "$N轻轻的搂着$n，双手从$n的脸颊慢慢的抚摸下去直至胸膛，只见$p"
              "不由的颤动了一下，一时间意乱情迷，双手紧紧的抱住了$N，把脸深"
              "深的埋在$N的怀中，磨擦着$P的胸口，霎时间满堂春意，锦绣亦添光"
              "华，两人渐渐的进入了忘我的状态。" NOR;
        msg1 = replace_string(msg, "$N", "你");
        msg1 = replace_string(msg1, "$n", woman->name());
        msg1 = replace_string(msg1, "$P", "你");
        msg1 = replace_string(msg1, "$p", "她");

        msg2 = replace_string(msg, "$N", man->name());
        msg2 = replace_string(msg2, "$n", "你");
        msg2 = replace_string(msg2, "$P", "他");
        msg2 = replace_string(msg2, "$p", "你");

        msg = replace_string(msg, "$N", man->name());
        msg = replace_string(msg, "$n", woman->name());
        msg = replace_string(msg, "$P", "他");
        msg = replace_string(msg, "$p", "她");

        msg1 = sort_string(msg1, 60);
        msg2 = sort_string(msg2, 60);
        msg  = sort_string(msg, 60);

        message("vision", msg1, man);
        message("vision", msg2, woman);
        message("vision", msg, environment(man), ({ man, woman }));      
        
        if( armor=query_temp("armor", me) && sizeof(armor) )
                me->force_me("remove all");

        if( armor=query_temp("armor", target) && sizeof(armor) )
                target->force_me("remove all");
                
        message_sort(HIM "$n闭上眼睛静静地躺在床上，感到自己身上的衣服一件一件的被脱掉，突然$n感到$N火烫的身体压上了自己...\n" NOR, 
                     man, woman);

        remove_call_out("do_loving");
        call_out("do_loving", 1, man, woman, 0); 

}

void do_loving(object me, object target, int n)
{
        remove_call_out("do_loving"); 
        message_sort(loving_msg[n], me ,target); 
        
        if (n == sizeof(loving_msg) - 1) 
        {
                remove_call_out("do_over");
                call_out("do_over", 3, me, target);
                return;
        }
        call_out("do_loving", 3, me, target, n + 1); 
        return;
}

void do_over(object me, object target)
{
        set_temp("last_makelove", time(), me);
        addn("sex/"+target->name(1), 1, me);
        addn("sex/times", 1, me);
        if( query("sex/times", me) == 1 )
                set("sex/first", target->name(1), me);

        set("jing", 20, me);
        set("qi", 50, me);

        set_temp("last_makelove", time(), target);
        addn("sex/"+me->name(1), 1, target);
        addn("sex/times", 1, target);
        if( query("sex/times", target) == 1 )
                set("sex/first", me->name(1), target);

        if( query("id", target) == query("couple/couple_id", me )
         && query("id", me) == query("couple/couple_id", target )
        &&  ! target->query_condition("huaiyun")
         && !query("couple/child_id", me )
         && !query("couple/child_id", target )
        &&  random(100) < 21)
        {
                message("shout",HIR"【家有喜事】："HIM"恭喜"HIY+query("name", me)+"("+query("id", me)+")"
                        HIM"与"HIY+query("name", target)+"("+query("id", target)+")"HIM"做了准父母。\n"NOR,
                        users());
                message_vision(HIY "\n$N突然觉得一阵做呕，旋即羞红着脸，咬咬牙想起了那个该死的。\n" NOR, target);
                message_vision(HIM"\n$N怀孕了。赶快通知孩子的爸爸"HIY+query("name", me)+"("+query("id", me)+")"HIM"啊？．．．\n"NOR,target);
                target->apply_condition("huaiyun", 1200);           
                set("longbak",query("long",  target), target);
                set("long", HIY"\n"+query("name", target)+"挺着个大肚子，一看就知道是怀孕了，混身散发出一股慈祥的母爱。\n"NOR, target);
        }
}

int help(object me)
{
        write(@HELP
指令格式 : makelove <id>
 
你可以用这个指令想你喜欢的人提出做爱的要求，当然要在安全的地
方。如果对方对你设置了no_tell 的选项，你就无法提出这个要求。
做爱以后会极大的消耗男方的精和气。

HELP );
        return 1;
}
