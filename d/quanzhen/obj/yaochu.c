// weapon: /d/zhongnan/obj/yaochu.c 
// sdong 08/06/98 
        
#include <weapon.h> 
        
inherit HAMMER; 
        
void create() 
{ 
        set_name("药锄", ({ "yao chu", "chu" }) ); 
        set_weight(1000); 
        /*if( clonep() ) 
                set_default_object(__FILE__); 
        else*/ { 
                set("unit", "把"); 
                set("long", sort_msg("这是一把全真教道长们用来专门采药用的药锄。经过了多人的"
                        "使用虽然锄身已经锈迹斑斑了，但是锄口还是那样的锋利。稍不小心就有可"
                        "能把药草挖断。你可以在来全真路上的树林中来采集所需要的药材。\n"));            
                set("value", 50); 
                set("material", "iron"); 
                set("wield_msg", "$N拿出一把$n，握在手中。\n"); 
                set("unwield_msg", "$N放下手中的$n。\n"); 
        } 
       
        init_hammer(5); 
        setup(); 
}        

void init() 
{ 
        object me = this_player(); 
        if( query("id", me) != "qiu chuji" && !wizardp(me) )
        { 
                set("no_drop",  "这么有用的东西怎么能扔了呢。\n"); 
                set("no_steal", "这个东西你偷不到。\n"); 
                set("no_get", "这个东西你不能拿。\n"); 
        } 
} 
