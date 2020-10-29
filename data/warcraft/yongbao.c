// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("卿吻[2;37;0m[2;37;0m", ({"qinwen"}));        
        set("gender", "男性");                
        set("long", "热情舌吻[2;37;0m
它是拥抱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yongbao");
        set("owner_name", "拥抱");
        set_temp("owner", "yongbao");
        set_temp("owner_name", "拥抱");
        ::setup();
}
