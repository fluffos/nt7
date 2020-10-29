void main(string idx)
{
        object tree = find_object("/u/redl/obj/luckytree#" + idx);
                mapping tob, gob, *gls = ({}); 
                string tname; 
                set("send_items_count", 0, tree); 
                        tob = ([ 
                        "id"    :               "ntb",
                        "file":"/u/redl/npc/obj/ntb", 
                        "amount":11 
                        ]);
                        tname = tob["file"]; 
                                tname = load_object(tname)->name(); 
                        tob += (["name":tname]); 
                        if (tob["amount"]<1) tob["amount"] = 1; 
                        addn("send_items_count", tob["amount"], tree); 
                        gls += ({tob}); 

        tob = ([ 
        "id"    :"wxts",
        "file":"/d/dongtian/obj/wanxiangbook", 
        "amount":222 
        ]);
        tname = tob["file"]; 
                tname = load_object(tname)->name(); 
        tob += (["name":tname]); 
        if (tob["amount"]<1) tob["amount"] = 1; 
        addn("send_items_count", tob["amount"], tree); 
        gls += ({tob}); 

        tob = ([ 
        "id":"ptao",
        "file":"/d/emei/obj/pantao", 
        "amount":1111 
        ]);
        tname = tob["file"]; 
                tname = load_object(tname)->name(); 
        tob += (["name":tname]); 
        if (tob["amount"]<1) tob["amount"] = 1; 
        addn("send_items_count", tob["amount"], tree); 
        gls += ({tob}); 
        set("gift_items", gls, tree); 
}
