#include <ansi.h>
//草类药材

inherit ITEM; 
mapping *ansi= ({
([     "yanse":    HIC,]),
([     "yanse":    HIG,]),
([     "yanse":    HIR,]),
([     "yanse":    HIB,]),
([     "yanse":    HIM,]),
([     "yanse":    HIY,]),
([     "yanse":    RED,]),
([     "yanse":    YEL,]), 
([     "yanse":    MAG,]),
([     "yanse":    CYN,]),

});
mapping *yao= ({
([     "name":     "鱼腥草",
       "id":       "yuxing cao",
       "yaoxing":  10000,
]),
([     "name":     "益母草",
       "id":       "yimu cao",
       "yaoxing":  20000,
]),
([     "name":     "藿香",
       "id":       "huo xiang",
       "yaoxing":  30000,
]),
([     "name":     "草珊瑚",
       "id":       "cao shanhu",
       "yaoxing":  40000,
]),
([     "name":     "穿心莲",
       "id":       "chuanxin lian",
       "yaoxing":  50000,
]),
([     "name":     "泽兰",
       "id":       "ze lan",
       "yaoxing":  60000,
]),
([     "name":     "绞股蓝",
       "id":       "jiaogu lan",
       "yaoxing":  70000,
]),
([     "name":     "虎耳草",
       "id":       "huer cao",
       "yaoxing":  80000,
]),
([     "name":     "金钱草",
       "id":       "jinqian cao",
       "yaoxing":  90000,
]),
});
void create()
{
    string name,id;
    int yaoxing,yaoo,yanse;

    yanse = random(sizeof(ansi));

    yaoo = random(sizeof(yao)); 

    name = yao[yaoo]["name"];

    id = yao[yaoo]["id"]; 

    yaoxing = yao[yaoo]["yaoxing"]; 

    //set_name(ansi[yanse]["yanse"]+name+NOR,({id}) );  
    set_name(name,({id}) );  

    set_weight(100);
    /*if( clonep() )
    set_default_object(__FILE__);
    else*/ {
         set("unit", "株");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
  set("setdbase", 1);
  set("autoload", 1);
   setup();
  }
