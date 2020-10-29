// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m朱雀[2;37;0m[2;37;0m", ({"zhu"}));        
        set("gender", "女性");                
        set("long", "time[2;37;0m
它是路过的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tamard");
        set("owner_name", "路过");
        set_temp("owner", "tamard");
        set_temp("owner_name", "路过");
        ::setup();
}
