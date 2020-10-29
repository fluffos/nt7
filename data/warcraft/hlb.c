// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是盘牛的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hlb");
        set("owner_name", "盘牛");
        set_temp("owner", "hlb");
        set_temp("owner_name", "盘牛");
        ::setup();
}
