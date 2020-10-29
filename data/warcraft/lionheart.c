// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m诺伦斯[2;37;0m[2;37;0m", ({"lion"}));        
        set("gender", "女性");                
        set("long", "神兽诺伦斯[2;37;0m
它是莱维的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lionheart");
        set("owner_name", "莱维");
        set_temp("owner", "lionheart");
        set_temp("owner_name", "莱维");
        ::setup();
}
