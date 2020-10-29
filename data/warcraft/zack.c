// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("月之女祭司[2;37;0m[2;37;0m", ({"ipencil"}));        
        set("gender", "女性");                
        set("long", "风云变色，欲海狂妮[2;37;0m
它是麻人周的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zack");
        set("owner_name", "麻人周");
        set_temp("owner", "zack");
        set_temp("owner_name", "麻人周");
        ::setup();
}
