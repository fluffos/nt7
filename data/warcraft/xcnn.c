// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m血红大逼[2;37;0m[2;37;0m", ({"xcnntt"}));        
        set("gender", "男性");                
        set("long", "$HIR$血淋淋大逼啊！！！[2;37;0m
它是胡摸的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xcnn");
        set("owner_name", "胡摸");
        set_temp("owner", "xcnn");
        set_temp("owner_name", "胡摸");
        ::setup();
}
