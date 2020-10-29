#include <ansi.h>
inherit ROOM;
string *s1 = ({ "问","苍","茫","大","地","谁","主","沉","浮","数","风","流",
                "人","物","还","看","今","朝","江","山","如","此","多","娇"});
void create()
{
        set("short", YEL"山庄正厅"NOR);
        set("long",
"你人尚未到，一丝淡淡的清香已自沁入你的心脾。走进大厅，迎面是\n"
"一幅极大的泼墨山水，墨迹纵横淋漓，笔锋峥嵘有致。画面上绘的是山河\n"
"社稷图，东起茫茫大海，西至皑皑雪山，气势不凡，令人顿生仰止之感，\n"
"旁边是一幅对联：「问苍茫大地谁主沉浮[2;37;0m数风流人物还看今朝\n"
"」[2;37;0m[2;37;0m横批：江山如此多娇[2;37;0m整座大厅虽然富丽\n"
"堂皇，气势恢宏，可是你总感觉有点不太协调的地方。似乎和你一路所见\n"
"所闻不太相象。你是不是应该好好(think)呢，然后再进去？\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "south" : __DIR__"dynamic/jiuqu16",
          "north" : __DIR__"neishi",
        ]));
        set("no_magic", "1");

        setup();
}

int init()
{
        add_action("do_think","think");
        add_action("do_uncover","uncover");
}

int do_think(string arg)
{
        object me;

        me = this_player();
        if( random(query("int", me))<20 )
        {
                write("你想啊想，结果想破了脑袋，白白的脑浆流了一地。\n");
                me->receive_damage("jing",100);
        }
        else
        {
                write("你闷头苦思，突然发现地上有一块方砖(brick)似乎边缘特别的光
滑。好象可以(uncover)\n");
                set_temp("marks/xanadu_hall1", 1, me);
        }
        return 1;
}

int do_uncover(string arg)
{
          object me;
        int i,j,k,l;

        me = this_player();
        if( !arg || arg != "brick" || !query_temp("marks/xanadu_hall1", me))// || wizardp(me) )
                return 0;
        message_vision(GRN"$N小心翼翼地把地板砖揭开，只听“叮”的一声轻响...\n"NOR,me);
       if( random(10) > 5 ) {
        message_vision(RED"一蓬牛毛细针向$N射来，正好命中，只听你一声惨嚎，细针已在你胸前对穿而过。\n"NOR,me);
                me->receive_wound("qi",random(query("kar", me))*50);
                COMBAT_D->report_status(me,me,1);
         }
        else
         message_vision(RED"一蓬牛毛细针向$N射来，$N轻松的躲了开去。\n"NOR,me);
         if( query("qi", me)>100 )
                {
                        delete_temp("marks/xanadu_hall1", me);
                        i=random(9);
                        j=random(9);
                        k=random(6);
                        l=random(6);
                        set_temp("marks/xanadu_hall2", l*1000+k*100+j*10+i, me);
 write("你惊魂甫定，发现地板翻起来的背面刻着一行小字："+s1[i]+s1[9+j]+s1[18+k]+s1[18+l]+"\n");


                }
        return 1;
}
