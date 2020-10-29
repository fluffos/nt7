 // Last Modified by Winder on Apr. 25 2001

#include <ansi.h>
inherit ITEM;
inherit F_QUEST;
#include "stuffs.h";

void create()
{
        set_name(WHT"白玉短笛"NOR, ({ "duandi", "di",}));
        set("weight", 100);
        seteuid(getuid());
        if(clonep()) set_default_object(__FILE__);
        else{
                set("unit", "只");
                set("long", WHT"这玉笛短得出奇，只不来七寸来长、通体洁白，晶莹可爱。\n" NOR);
                set("value", 50); 
                set("no_get", 1);
                set("di_number", 0);
                set("no_drop", 1);
        }
        setup();
}

void init()
{
        add_action("mark_success", "sign");
        add_action("set_task", "blow");
        add_action("set_task", "chui");
        add_action("report_task", "report");
}

mapping get_stuffs()
{
        mapping quest = stuffs[random(sizeof(stuffs))];
        quest += (["time" : time()+quest["exp_reward"]*30,
                "last_id" : quest["id"],
                "type" : "找" ]);
        return quest;
}
int set_task(string arg)
{
        object where, me = this_player();  
        mapping quest;
        where = environment(me);

        if( !arg ) return 0;
        if( !this_object()->id(arg)) return 0;

        if( me->is_busy() || me->is_fighting()) 
                return notify_fail("你正忙着呢。\n");    
        if( query("xx_user", this_object()) != getuid(me) )
                return notify_fail("拿着只别人的笛子吹？\n");    
        if( !(query("outdoors", where)) )
                return notify_fail("你在屋里吹笛子，笛声怎么可能传得远呢？\n");
        if(me->query_condition("gb_songxin") )
                return notify_fail("老仙最讨厌臭叫化子，先扔掉你的丐帮帮务再说！\n");
        if( query_temp("xx/id", me) )
                return notify_fail("你现在正在执行任务中。\n");  
        if(me->query_condition("job_busy")) 
                return notify_fail("你刚要完任务，先等等吧。\n");           
        if(me->query_condition("wait_xx_task")) 
                return notify_fail("上次搞砸了，这次你就等等吧。\n");      
        tell_room(environment(me),HIY+me->name()+"拿起一只"+query("name", this_object())+HIY"放到口边，轻轻一吹，发出一股尘锐的哨声。本来笛声清扬激越，\n但这根玉笛中发出来的声音却十分凄厉，全非乐调。\n"NOR,({me}));
        tell_object(me,HIY"你拿起"+query("name", this_object())+HIY"放到口边，轻轻吹了起来。\n"NOR);
        if( (query("outdoors", where)) != "xingxiu" && 
                (query("outdoors", where)) != "xiyu" )
                return notify_fail("此地和星宿海相离太远，信鸽恐怕听不到笛声。\n"); 
        if(random(2)==1)
        {
                if(!mapp(quest = get_quest(me, 0, "杀"))) 
                quest = get_stuffs();
        }
        else quest = get_stuffs();
        set_temp("quest", quest, me);
        me->start_busy(1);          
        me->apply_condition("job_busy", 30);   
        remove_call_out("report");
        call_out("report", 1, me);
        return 1;
}
int report(object me)
{        
        if(!me) return 0;
  
        if( me->is_busy() || me->is_fighting()) 
                return notify_fail("你正忙着呢。\n");   
        if( !query_temp("quest/id", me) )
                return notify_fail("你现在还没有接收到任何任务。\n");
   
        message_vision(HIW"\n只见天空中飞下一只白色信鸽，降在$N的肩头。\n\n"NOR,me);
        message_vision("$N将书信从白鸽身上解下，瞟了一眼。\n",me);
        tell_object(me,"信中写道： \n老仙最近的意思可能是想要");
        if( query_temp("quest/type", me) == "杀" )
                tell_object(me,"杀掉「"+query_temp("quest/name", me)+"("+query_temp("quest/id", me)+")」。\n\n");
        else
                tell_object(me,"得到「"+query_temp("quest/name", me)+"("+query_temp("quest/id", me)+")」。\n\n");
        tell_object(me, "目前情况可以通过查看任务(report)来了解。\n");
        return 1;       
}
int report_task()
{
        int time;
        object me = this_player();
        time=query_temp("quest/time", me);
  
        if (!time) return notify_fail("你现在还没有接收到任何任务。\n");
        write("你目前的任务目标是：\n\n");
   
        if( query_temp("quest/type", me) == "杀" )
                write("杀掉「"+query_temp("quest/name", me)+"("+query_temp("quest/id", me)+")」。\n\n并在尸体上留下(signcorpse)我们星宿派的标志。\n");
        else
                write("找到「"+query_temp("quest/name", me)+"("+query_temp("quest/id", me)+")」，献(xian)给老仙。\n\n");
   
        tell_object(me, "你必须在"+get_time(time)+"之前完成任务！\n\n");
        return 1;
}
int mark_success(string arg)
{
        object target, me = this_player();
        string last;
  
        if(!arg) return notify_fail("你要干什么？\n");
        if(!objectp(target = present(arg, environment(me))))
                return notify_fail("找不到这个东西。\n");
        if( me->is_busy() || me->is_fighting()) 
                return notify_fail("你正忙着呢。\n");    
        switch (is_target(target, me))
        {
                case 0:  return 0;
                case -1: tell_object(me, "耶？有让你去杀人了吗？\n");
                        return 0;
                case -2: tell_object(me,"笨蛋，你杀错人了！\n");
                        return 0;
                case -3: tell_object(me,"糟了，时间已经过了！\n");
                        last=query_temp("quest/last_id", me);
                        delete_temp("quest", me);
                        set_temp("quest/last_id", last, me);
                        me->apply_condition("wait_xx_task", 40); 
                        return 0;
                case -4: tell_object(me,"哦，这人和NPC同名？算他倒霉！\n");
                        return 0;
                default: break;
        }
        if( query("family/family_name", me) == "星宿派" )
        {
                message_vision(HIR"\n$N左手一扬，衣袖中飞出一点"BLU"蓝印印"HIR"的火花，嗤嗤做响，射向$n，着体便燃！\n\n"NOR, me, target);
                set("name", HIB"烧焦的尸体"NOR, target);
                set("long", HIB"一具被炼心弹烧焦的尸体，焦臭四溢，情状可怖。\n"NOR, target);
                addn("xx_points", 1, me);
        }
        else
        {
                message_vision("$N哼了一声，用墨笔在$n的衣袖上写下了“星宿”二字。\n", me, target);
                set("long",query("long",  target)+"\n上面有人写了大大的"HIB"星宿"NOR"二字。\n", target);
        }
        call_out("done", 1, me);   
        me->start_busy(1);    
        return 1;
}      
void done(object me)
{
        int num,times,score;
        mapping quest,fam;
        if(!me) return;
        quest=query_temp("quest", me);
        
        num=query("perform/number", me)+1;
        if (num<4) times=num;
         else times=4;
        
        if( !(fam=query("family", me)) || fam["family_name"] != "星宿派")score=0;
         else score=random(10)+ 10 * times;        
        
        addn("combat_exp", quest["exp_reward"], me);
        addn("potential", quest["pot_reward"], me);
        addn("family/fealty", score, me);
        
        tell_object(me, "好！任务完成，你马上做了一封飞鸽传书送回星宿海。\n");
        tell_object(me, GRN"你获得"+chinese_number(quest["exp_reward"])+"点经验和"+chinese_number(quest["pot_reward"])+"点潜能和"+chinese_number(score)+"点忠诚度的奖励！\n"NOR);

        
        addn("shen", -(quest["exp_reward"]*15), me);
        delete_temp("quest", me);
        set_temp("last_id", quest["last_id"], me);
//        me->apply_condition("job_busy", 3);  
        me->clear_condition("job_busy");
        return;
}