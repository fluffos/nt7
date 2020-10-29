//Room: /d/dali/bingying.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","兵营");
        set("long", @LONG
大理国虽小，却重视精兵良将。然屈人必先屈志，兵戈乃下下之
策，段氏大理先与北邻宋朝修和，再以姻亲拉拢当地人，多年无战事。
这是城里的铁骑营，为皇族的嫡系，装备给养无不优于中原地方。军
士们严缜以待，盔甲鲜明，刀剑锋利。
LONG );
        set("objects", ([
           "/d/dali/npc/bing": 2,
           "/d/dali/npc/weishi1": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/dahejiewest",
            "west"   : "/d/dali/majiu",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}