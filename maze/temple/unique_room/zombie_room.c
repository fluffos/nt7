#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIC"失落神庙"NOR);
        set("long", @LONG
神庙很大，柱子上雕刻着千奇百怪的动物，有的人身上却
长着一颗狼头，人身上生出一双翅膀，怪异的怪首的雕刻让人
叹为观止，庙顶成八角，屋脊曲线柔美,泥塑,剪黏,木雕,彩绘
皆为上品。
LONG);
        
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);       
        set("objects",([
                "/maze/temple/npc/zombie": 10,  
                "/maze/temple/npc/zombie_lord": 3,
                "/maze/temple/npc/zombie_king": 1,
        ]));
        setup();
}

