inherit ROOM;

void create()
{
        set("short", "客厅");
        set("long", @LONG
这是一间宽敞的大厅，地上用大理石铺就的地面被打磨的像
镜子一样光滑，正中的三级台阶上摆放着一长红木大太师椅，椅
子的绸面上绣着狼虫虎豹，非常威严。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"fyuan",
]));

        set("objects", ([
//        __DIR__"npc/guanjia" : 1,

]));

        setup();
        replace_program(ROOM);
}
