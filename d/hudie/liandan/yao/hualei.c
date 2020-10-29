#include <ansi.h>
//花类药材

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
([     "name":     "红花",
       "id":       "hong hua",
       "yaoxing":  100,
]),
([     "name":     "丁香",
       "id":       "ding xiang",
       "yaoxing":  200,
]),
([     "name":     "木槿",
       "id":       "mu jin",
       "yaoxing":  300,
]),
([     "name":     "莲花",
       "id":       "lian hua",
       "yaoxing":  400,
]),
([     "name":     "金银花",
       "id":       "jinyin hua",
       "yaoxing":  500,
]),
([     "name":     "菊花",
       "id":       "ju hua",
       "yaoxing":  600,
]),
([     "name":     "月季",
       "id":       "yue ji",
       "yaoxing":  700,
]),
([     "name":     "腊梅",
       "id":       "la mei",
       "yaoxing":  800,
]),
([     "name":     "辛夷",
       "id":       "xin yi",
       "yaoxing":  900,
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
         set("unit", "朵");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }
