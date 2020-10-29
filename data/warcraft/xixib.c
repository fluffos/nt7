// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("笔飞翔[2;37;0m[2;37;0m", ({"xixibbb"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是洗笔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xixib");
        set("owner_name", "洗笔");
        set_temp("owner", "xixib");
        set_temp("owner_name", "洗笔");
        ::setup();
}
