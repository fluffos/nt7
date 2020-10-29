// huaiyun.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int birth1(object me);
int birth2(object me);
int birth3(object me);

int update_condition(object me, int duration)
{
        if (duration < 1) return 0; 

        if (duration == 1200)
        {
                tell_object(me, HIY "你觉得周围的人好象都在偷偷看你，心里好不自在！\n" NOR);
                message("vision", me->name() + HIY "羞涩的低着头，摆弄着自己的衣角。\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 800)
        {
                tell_object(me, HIY "你觉得周围的人都好奇怪，对你指指点点，真是讨厌！\n" NOR);
                message("vision", me->name() + HIY "瞪着你，好象你欠了她什么似的……\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 400)
        {
                tell_object(me, HIY "你觉得周围的人都在笑嘻嘻的看着你，可能他们已经看出来了你……。\n" NOR);
                message("vision", me->name() + HIY "用一种异常慈祥的目光，反复打量着自己的肚子。\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 200)
        {
                tell_object(me, HIY "你觉得周围的人与世界都是那麽的美好，心情无比的舒畅！\n" NOR);
                message("vision", me->name() + HIY "一身充满了安详的气息，那积聚着母爱的目光不时扫视着周围！\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 20 || duration == 10)
        {
                tell_object(me, HIY "你觉得周围的人都用着极其关切的目光注视着你，难道是……快了？\n" NOR);
                message("vision", me->name() + HIY "已经行动十分的迟缓了，不时的停下来喘气。\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 1)
        {
                tell_object(me, HIY "周围的人都惊讶的合不上了嘴巴，一定是见到了什么奇怪事情！\n"
                                "看来你是马上就要生了，请赶紧和孩子的父亲去扬州药铺的二楼产房，否则会有生命危险的！\n" NOR);
                message("vision", me->name() + HIY "捂着大大的肚子，蹲在了地上，脸上一副极其痛苦的神情！\n" NOR,
                        environment(me), me);
                remove_call_out("birth1");
                call_out("birth1", 100, me);
        }
        me->apply_condition("huaiyun", duration - 1);
        return 1;
}

int birth1(object me)
{
        object target;        
        
        if( (query("age", me))<18 )
        {
                message_vision(HIY "\n$N似乎觉得腹中一阵巨痛，大叫一声，由于$N年龄太小，不适合生育，\n所以$N的孩子流产了，好可怜啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        } 
        
        if (base_name(environment(me)) != "/d/city/chanfang")
        {
                message_vision(HIY "\n$N似乎觉得腹中一阵巨痛，大叫一声，由于这里的环境实在是太恶劣了，\n所以$N的孩子流产了，好可怜啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }
         
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N似乎觉得腹中一阵巨痛，大叫一声，由于关键时刻你的男人没有守侯在身边，\n所以$N的孩子流产了，好可怜啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }
        
        if (! me->is_busy())
                me->start_busy(15);
        if (! target->id_busy())
                target->start_busy(15);
                
        message_vision(HIY "\n$N忽觉腹中一阵颤动，赶紧拉住$n的手，柔声说道：要生了! \n" NOR, me, target);
        remove_call_out("birth2");
        call_out("birth2", 15, me);
      
        return 1;
}

int birth2(object me)
{        
        object target;
         
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N似乎觉得腹中一阵巨痛，大叫一声，由于关键时刻你的男人没有守侯在身边，\n所以$N的孩子流产了，好可怜啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }  
              
        if (! me->is_busy())
                me->start_busy(15);
        if (! target->id_busy())
                target->start_busy(15);
                        
        message_vision(HIY "\n$N已是大汗淋漓，一直都在呼天抢地，双手紧紧扣住$n的手不放。\n\n婴儿已经探出了头．．．\n" NOR, me, target);
        remove_call_out("birth3");
        call_out("birth3", 15, me);
        return 1;
}

int birth3(object me)
{
        object target;
        object baby;
        
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N似乎觉得腹中一阵巨痛，大叫一声，由于关键时刻你的男人没有守侯在身边，\n所以$N的孩子流产了，好可怜啊！\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }  
                
        message_vision(HIY "\n「哇」．．．，婴儿出世了！\n" +
                "\n$N面色苍白，斜倚在床头，看看孩子满意地露出一丝微笑。\n" NOR, me, target);
        set("long", "\n她看起来已经是一个成熟的少妇了哦。\n"NOR, me);
        delete("longbak", me);

        set("neili", 0, me);
        set("qi", 1, me);
        set("jing", 1, me);
        
        baby = new("/clone/user/baby");
        if (random(2) > 0)
        {
                set("gender", "男性", baby);
                baby->set_name("小"+query("name", target),
                               ({"xiao_"+query("id", target),"baby"}));
                               
                set("long", "这是"+query("name", target)+"和"+query("name", me)+"的孩子。长的好象"+query("name", target)+"啊！\n", baby);
                message("shout",HIR"【家有喜事】"HIM"恭喜"HIR+query("name", me)+"("+query("id", me)+")"
                        HIM"给"HIR+query("name", target)+"("+query("id", target)+")"HIM"添了一个大胖小子。\n"NOR,
                        users());
        } else
        {
                set("gender", "女性", baby);
                baby->set_name("小"+query("name", me),
                               ({"xiao_"+query("id", me),"baby"}));
                               
                set("long", "这是"+query("name", target)+"和"+query("name", me)+"的孩子。长的好象"+query("name", me)+"啊！\n", baby);
                message("shout",HIR"【家有喜事】"HIM"恭喜"HIR+query("name", me)+"("+query("id", me)+")"
                        HIM"给"HIR+query("name", target)+"("+query("id", target)+")"HIM"添了一个千金小宝贝。\n"NOR,
                        users());                
        }
        
        set("per", (query("per", me)+query("per", target))/2, baby);
        set("kar", (query("kar", me)+query("kar", target))/2, baby);
        set("int", (query("int", me)+query("int", target))/2, baby);
        set("str", (query("str", me)+query("str", target))/2, baby);
        set("con", (query("con", me)+query("con", target))/2, baby);
        set("dex", (query("dex", me)+query("dex", target))/2, baby);
        set("parents/father",query("id",  target), baby);
        set("parents/mother",query("id",  me), baby);
        baby->save();
        
        set("couple/child_id",query("id",  baby), me);
        set("couple/child_name",query("name",  baby), me);
        set("couple/child_id",query("id",  baby), target);
        set("couple/child_name",query("name",  baby), target);
        me->save();
        target->save();
        
        if (! baby->move(environment(me)))
                baby->move(environment(environment(me)));
                
        return 1;
}