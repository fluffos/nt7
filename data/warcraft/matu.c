// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹黄[2;37;0m[2;37;0m", ({"matupet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是黄壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matu");
        set("owner_name", "黄壹");
        set_temp("owner", "matu");
        set_temp("owner_name", "黄壹");
        ::setup();
}
