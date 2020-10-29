// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火鸟[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "男性");                
        set("long", "四大神兽[2;37;0m
它是邪君的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "miniqz");
        set("owner_name", "邪君");
        set_temp("owner", "miniqz");
        set_temp("owner_name", "邪君");
        ::setup();
}
