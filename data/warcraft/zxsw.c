// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("暗夜[2;37;0m[2;37;0m", ({"anye"}));        
        set("gender", "男性");                
        set("long", "暗夜的颜色[2;37;0m
它是唐无血的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zxsw");
        set("owner_name", "唐无血");
        set_temp("owner", "zxsw");
        set_temp("owner_name", "唐无血");
        ::setup();
}
