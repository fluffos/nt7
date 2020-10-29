// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m太[1;33m古[1;32m麒[1;31m麟[2;37;0m[2;37;0m", ({"xql"}));        
        set("gender", "男性");                
        set("long", "来自鸿蒙太古时代开天辟地的第一只麒麟，号称祥瑞麒麟。[2;37;0m
它是疯小邪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xieyi");
        set("owner_name", "疯小邪");
        set_temp("owner", "xieyi");
        set_temp("owner_name", "疯小邪");
        ::setup();
}
