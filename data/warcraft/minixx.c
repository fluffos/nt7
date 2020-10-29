// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小青龙[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "男性");                
        set("long", "四大神兽之一[2;37;0m
它是海纳的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "minixx");
        set("owner_name", "海纳");
        set_temp("owner", "minixx");
        set_temp("owner_name", "海纳");
        ::setup();
}
