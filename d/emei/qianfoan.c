#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "千佛庵");
        set("long", @LONG
此处是洪椿坪千佛庵。山间小坪坝，四面层峦叠障，峰环岭护；
两侧深谷幽岚，溪涧玲叮。坪上古木扶疏，亭亭如盖山阴沁透，白雾
飘游，极为幽静清凉。此处常见雨雾霏霏，林中迷迷蒙蒙，乃山中雾
气所为。正所谓「山行本无雨，空翠湿人衣」。这就是誉为奇观的「
洪椿晓雨」。此处殿美景幽，气象新异，令人心醉。沿途南上是「九
十九道拐」，北下经黑龙江栈道至清音阁。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "westup" : __DIR__"jsjdg1",
          "east"   : __DIR__"heilong2",
          "enter"  : __DIR__"qfadadian",
      ]));
      set("coor/x", -470);
        set("coor/y", -240);
        set("coor/z", 100);
        set("coor/x", -470);
        set("coor/y", -240);
        set("coor/z", 100);
        setup();
}

int valid_leave(object me, string dir)
{
        int c_skill;

        me = this_player();
        if (dir == "westup")
        {
                c_skill = me->query_skill("dodge", 1);
                if( query("qi", me)>40 )
                {
                        me->receive_damage("qi", 20 + random(20));

                        if (me->can_improve_skill("dodge") && c_skill < 100)
                                me->improve_skill("dodge", 1 + c_skill / 15);

                        tell_object(me, HIC "你爬上九十九道拐，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不动了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}