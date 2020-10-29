// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m火麒麟[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是精忠报国的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "blina");
        set("owner_name", "精忠报国");
        set_temp("owner", "blina");
        set_temp("owner_name", "精忠报国");
        ::setup();
}
