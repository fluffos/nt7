//redl 2014

#include <ansi.h>
inherit F_CLEAN_UP;  

int main(object me, string arg)  
{
        object ob;
        object item;

        if (! SECURITY_D->valid_grant(me, "(arch)")) 
                return 0;
        if( !arg || arg == "" ) return 0;
        ob = find_player(arg);
        if( !ob ) return 0;


              item = new("/clone/medicine/jiuhua"); 
              item->set_amount(20); 
                          item->move(ob, 1); 
              item = new("/d/dongtian/obj/wanxiangbook"); 
              item->move(ob, 1); 
              item = new("/d/dongtian/obj/wanxiangbook"); 
              item->move(ob, 1); 
              item = new("/d/dongtian/obj/wanxiangbook"); 
              item->move(ob, 1); 
        item = new("/clone/gift/jiuzhuan");
        item->set_amount(30);
        item->move(ob, 1);
        item = new("/clone/gift/xuanhuang");
        item->set_amount(25);
        item->move(ob, 1);
        item = new("/clone/fam/max/xuanhuang");
        item->set_amount(1);
        item->move(ob, 1);
        item = new("/clone/fam/max/longjia");
        item->set_amount(1);
        item->move(ob, 1);
        item = new("/clone/fam/max/zhenyu");
        item->set_amount(1);
        item->move(ob, 1);
        item = new("/clone/gift/puti-zi");
        item->set_amount(35);
        item->move(ob, 1);
        item = new("/clone/gift/tianxiang");
        item->set_amount(30);
        item->move(ob, 1);
        item = new("/clone/fam/gift/int3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/int3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/str3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/str3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/dex3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/dex3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/con3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/con3");
        item->move(ob, 1);
        item = new("/clone/goods/dizangshi");
        item->move(ob, 1);
        item = new("/clone/money/thousand-gold");
        item->set_amount(200);
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/medicine/yuqingwan");
        item->set_amount(10);
        item->move(ob, 1);
        item = new("/clone/medal/yongshi_xunzhang");
        item->move(ob, 1);
        item = new("/clone/medal/vip_xunzhang");
        item->move(ob, 1);
        item = new("/clone/medal/diamond_xunzhang");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_armor");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_head");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_boots");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_surcoat");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_waist");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_wrists");
        item->move(ob, 1);
        item = new("/clone/goods/wisdom_cloth");
        item->move(ob, 1);
        item = new("/u/redl/obj/fanghuamu");
        item->move(ob, 1);
             item = new("/clone/goods/tianshi-charm"); 
             item->move(ob, 1); 
             item = new("/clone/goods/tianshi-charm"); 
             item->move(ob, 1); 
             item = new("/clone/goods/tianshi-charm"); 
             item->move(ob, 1); 
        item = new("/clone/goods/tianjing");
        item->move(ob, 1);
  addn("flowers/amount",10,ob);
        tell_object(ob, "\a", 0); 
  tell_object(ob, HIY"一阵祥风拂面而来，你得到天神"+query("id",me)+"的馈赠！\n"NOR); 
  tell_object(ob, HIY"一阵祥风拂面而来，你得到十朵鲜花，输入flowers查看。\n"NOR); 
  tell_object(ob, HIY"一阵祥风拂面而来，你行囊里多了些东西，输入i查看。\n"NOR); 
        write("ok.\n");
        return 1;
}


