// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫[2;37;0m[2;37;0m", ({"lisam"}));        
        set("gender", "男性");                
        set("long", "小猫[2;37;0m
它是慕容低落的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lisamina");
        set("owner_name", "慕容低落");
        set_temp("owner", "lisamina");
        set_temp("owner_name", "慕容低落");
        ::setup();
}
