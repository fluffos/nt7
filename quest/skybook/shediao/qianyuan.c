

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "skybook/shediao/风雪惊变/"

void create()
{
	set("short", GRN "前院" NOR);
	set("long",@long
这里是杨铁心家的前院，院子由篱笆和竹子编成的栅栏，院子里放着一个铁犁，显得格外苍凉。
long);
        set("outdoors", "jiaxing");
	set("exits",([
		"north" : __DIR__"yangjia",
		"south" : __DIR__"njroad3",
        ]));
        set("quest",1);
	set("no_fight", 1);
	setup();
}
int valid_leave(object me, string dir)
{
        if( dir == "north" && !query(QUESTDIR+"over",me) )
                return notify_fail(RED"没有主人的允许你不可以去人家家里。\n"NOR);
        if(dir == "north" && me->query_condition("killer")) 
   	        return notify_fail(RED"没有主人的允许你不可以去人家家里。\n"NOR);
        return ::valid_leave(me, dir);
}

void init()
{
        object me;
        me = this_player();
        if( query(QUESTDIR+"start", me) )
                me->start_busy(1);
        if( query(QUESTDIR+"start", me)
	    && !query(QUESTDIR+"over", me)
            && !query_temp(QUESTDIR+"kill", me) ) {
                tell_object(me,YEL"只听得众兵丁齐声叫喊：“捉拿反贼，莫让反贼逃了！””\n"NOR); 
                tell_object(me,YEL"忽听一名武将高声叫道：“郭啸天、杨铁心两名反贼，快快出来受缚纳命。”\n"NOR);       
                remove_call_out("goyangjia");
                call_out("goyangjia", 3, me);      
                write(CYN"\n你不由感到十分好奇，你停了下来，静静倾听。\n"NOR);
        } else {  
                remove_call_out("greeting");
                call_out("greeting", 4, me);   
        }
}
void greeting(object me)
{
        int shen;
        if( !me ) return;
        if( !present(me, this_object()) ) return;
        if( query(QUESTDIR+"start", me)) return;
        shen = query("shen", me);
        if( shen < 0 ) 
                tell_object(me,HIR"只听门内一个深沉浑厚的声音传来：看你一身邪气，还请离开！\n"NOR);
        else 
                tell_object(me,HIR"只听门内一个深沉浑厚的声音传来：这位少侠，还请离开！\n"NOR);
}
void goyangjia(object me)
{
        if( !me ) return;
        if( !present(me,this_object()) )
        {
                tell_object(me,HIY"你擅自离开牛家村杨家前院，错过了精彩的一幕。\n"NOR);
                //log_file("quest/SheDiao", sprintf("%s(%s)初进牛家村杨家前院，却擅自离开，失败。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
                delete_temp(QUESTDIR+"start", me);
                return;
        }

        tell_object(me,YEL"\n你听到杨铁心低说道：“官家不知为了何事，竟来污害良民。跟官府是辩不清楚的，咱们只好逃命。你别慌，凭我这杆枪，定能保你冲出重围。”\n"NOR); 
        tell_room(environment(me), YEL+me->name()+"一想大侠杨铁心要突受危难，猛然冲进杨家去救杨铁心！\n" NOR, ({me}));
        //log_file("quest/SheDiao", sprintf("%s(%s)初进牛家村杨家前院。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
        me->move(__DIR__"yangjia");  
}
