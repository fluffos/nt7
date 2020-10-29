// Room: 八卦图

#include <ansi.h>
inherit ROOM;
string* dirs = ({
        "坎", "坤", "离", "乾",
        "艮", "震", "巽", "兑"
        });
void create()
{
        set("short",HIR"八阵图"NOR);
        set("long", @LONG
你一踏进阵中只觉得四周变得天昏地暗。这里横七竖八的堆放着
各种巨石，细心一看发觉每个石头摆放位置恰到好处，暗合八卦原理
，相传是三国时代诸葛亮留下来的阵法，环环想扣，若想出过此阵并
非易事。
LONG
);            
        set("outdoors","tianyu");
        set("exits", ([
                "坎" : __DIR__"baguaz0",
                "坤" : __DIR__"baguaz0",
                "离" : __DIR__"baguaz0",
                "乾" : __DIR__"baguaz0",
                "艮" : __DIR__"baguaz1",
                "震" : __DIR__"baguaz1",
                "巽" : __DIR__"baguaz1",
                "兑" : __DIR__"baguaz1",
        ]));
        setup();
}
void init()
{
        object ob = this_player();
        int step, temp, count;
        if ( !ob->query_temp("bagua_start"))
        {
                ob->set_temp("bagua_start", 1);
                ob->set_temp("bagua_step", 1);
                ob->set_temp("bagua_temp", 0);
                ob->set_temp("bagua_count", 1);
        }
        temp  = ob->query_temp("bagua_temp");
        count = ob->query_temp("bagua_count");
        temp  = temp * 2;
        if (count < 3)
        {
                count++;
        }
        else
        {
                count = 1;
                step = ob->query_temp("bagua_step");
                if (temp == ob->query_temp("bagua_" + step))
                 {
                        if (step == 8)
                         {
                                ob->delete_temp("bagua_start");
                                ob->delete_temp("bagua_step");
                                ob->delete_temp("bagua_temp");
                                ob->delete_temp("bagua_count");
                                write(HIC"你反踏“震”位，扑“乾”位，突然眼前一亮，"+HIR+dirs[random(sizeof(dirs))]+HIC+"位上现出空位，你赶忙踏了过去。\n"NOR);
                                ob->move(__DIR__"qilindong", 1);
                                ob->set_temp("bagua_over",1);
                                tell_room(environment(ob), "突然，石阵中现出一个缺口，" + ob->name() + "赶紧闪身而出。\n");
                                return;
                        }
                        tell_object(ob,HIY"你发现刚才走过的路径暗合八卦，心中若有所悟！\n"NOR);
                        ob->add_temp("bagua_step", 1);
                }
                else
                 {
                        ob->delete_temp("bagua_start");
                        ob->delete_temp("bagua_step");
                        ob->delete_temp("bagua_temp");
                        ob->delete_temp("bagua_count");
                        write(CYN"你发觉自己踩错了方位，阵中石阵更加变幻末测了，只好赶快抢回起始点！\n");
                        ob->move(__DIR__"dongkou");
                        tell_room(environment(ob), HIR"只见" + ob->name() + 
                                    "朗朗跄跄从石阵中退了出来。\n"NOR);
                        return;
                }
                temp = 0;
        }
        ob->set_temp("bagua_temp", temp);
        ob->set_temp("bagua_count", count);
}


