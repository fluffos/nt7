// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m苹果[2;37;0m[2;37;0m", ({"apple"}));        
        set("gender", "男性");                
        set("long", "这是苹果的坐骑[2;37;0m
它是彩韵亨菲的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ysduanp");
        set("owner_name", "彩韵亨菲");
        set_temp("owner", "ysduanp");
        set_temp("owner_name", "彩韵亨菲");
        ::setup();
}
