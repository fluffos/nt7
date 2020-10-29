// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m墨玉麒麟[2;37;0m[2;37;0m", ({"mmp"}));        
        set("gender", "女性");                
        set("long", "$HIB$墨玉麒麟[2;37;0m
它是枫之幻的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maplea");
        set("owner_name", "枫之幻");
        set_temp("owner", "maplea");
        set_temp("owner_name", "枫之幻");
        ::setup();
}
