// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[44m[1;32m四不象[2;37;0m[2;37;0m", ({"sibuxiang"}));        
        set("gender", "女性");                
        set("long", "$BBLU$$HIG$四不象[2;37;0m
它是慕容雅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "iii");
        set("owner_name", "慕容雅");
        set_temp("owner", "iii");
        set_temp("owner_name", "慕容雅");
        ::setup();
}
