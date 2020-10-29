// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("最爱白虎[2;37;0m[2;37;0m", ({"hllddbh"}));        
        set("gender", "女性");                
        set("long", "最爱白虎[2;37;0m
它是文东四号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hlldd");
        set("owner_name", "文东四号");
        set_temp("owner", "hlldd");
        set_temp("owner_name", "文东四号");
        ::setup();
}
