// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("格力霸[2;37;0m[2;37;0m", ({"geliba"}));        
        set("gender", "男性");                
        set("long", "雄壮威武[2;37;0m
它是牛肉火锅的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fxtx");
        set("owner_name", "牛肉火锅");
        set_temp("owner", "fxtx");
        set_temp("owner_name", "牛肉火锅");
        ::setup();
}
