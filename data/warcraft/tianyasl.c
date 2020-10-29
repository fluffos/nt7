// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦我[2;37;0m[2;37;0m", ({"owew"}));        
        set("gender", "男性");                
        set("long", "哦我[2;37;0m
它是和平年代的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tianyasl");
        set("owner_name", "和平年代");
        set_temp("owner", "tianyasl");
        set_temp("owner_name", "和平年代");
        ::setup();
}
