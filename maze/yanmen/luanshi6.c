
inherit DEMONROOM;

void create()
{
        set("short", HIW"乱石路"NOR);
        set("long", @LONG
这里是雁门关的乱石路, 是扼守南北的交通必经之路，历来为兵家必
争之地，由山顶币制而下，只有一条狭窄的羊肠小道，两面则是堆满乱石，
好象暗浮杀机。
LONG
        );
        set("outdoors", "yanmen");
        set("exits", ([
                "north" :  __DIR__"luanshi5",
                "south" :  __DIR__"luanshi7",
        ]));
        set("no_fly",1);
        set("n_time", 30); 
        set("n_npc", 5); 
        set("n_max_npc", 15);
        set("s_npc", __DIR__"npc/qidanbing");

        setup();
}
