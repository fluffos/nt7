// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m[30m愤怒的小鸟[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "女性");                
        set("long", "$HIR$$BLK$愤怒的小鸟[2;37;0m
它是犀利哥的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "siong");
        set("owner_name", "犀利哥");
        set_temp("owner", "siong");
        set_temp("owner_name", "犀利哥");
        ::setup();
}
