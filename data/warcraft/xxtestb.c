// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m白术[2;37;0m[2;37;0m", ({"xxtestbb"}));        
        set("gender", "男性");                
        set("long", "a [2;37;0m
它是星宿白术的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xxtestb");
        set("owner_name", "星宿白术");
        set_temp("owner", "xxtestb");
        set_temp("owner_name", "星宿白术");
        ::setup();
}
