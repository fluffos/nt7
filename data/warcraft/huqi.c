// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m魔妲己[2;37;0m[2;37;0m", ({"jhuli"}));        
        set("gender", "男性");                
        set("long", "妖娆的九尾狐狸----妲己[2;37;0m
它是胡老七的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "huqi");
        set("owner_name", "胡老七");
        set_temp("owner", "huqi");
        set_temp("owner_name", "胡老七");
        ::setup();
}
