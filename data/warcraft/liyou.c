// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m千[1;34m鸟[1;37m朝[1;31m凤[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "此乃千鸟之王[2;37;0m
它是小金人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "liyou");
        set("owner_name", "小金人");
        set_temp("owner", "liyou");
        set_temp("owner_name", "小金人");
        ::setup();
}
