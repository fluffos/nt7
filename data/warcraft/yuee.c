// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("喵喵[2;37;0m[2;37;0m", ({"lucas"}));        
        set("gender", "男性");                
        set("long", "萌萌哒[2;37;0m
它是沐沐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yuee");
        set("owner_name", "沐沐");
        set_temp("owner", "yuee");
        set_temp("owner_name", "沐沐");
        ::setup();
}
