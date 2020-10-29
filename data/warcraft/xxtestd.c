// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m甘草[2;37;0m[2;37;0m", ({"xxtestdd"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是星宿甘草的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xxtestd");
        set("owner_name", "星宿甘草");
        set_temp("owner", "xxtestd");
        set_temp("owner_name", "星宿甘草");
        ::setup();
}
