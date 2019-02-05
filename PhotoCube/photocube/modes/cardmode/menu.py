def __createImageContextMenu( self ):
    button_width = 5
    menu_items = ['edit tags', 'Cancel']
    
    tagListItems_context = DirectScrolledList(text_fg=(1,1,1,1), 
        text_shadow=(0,0,0,1), 
        #frameColor=FRAME_COLOR, 
        frameSize=(-5.1, 5.1, -0.7, 1.15),
        borderWidth=(0.1,0.1), 
        relief=DGG.RIDGE, 
        text="", 
        forceHeight=1.6,
        scale=0.035,
        items = menu_items,
        numItemsVisible=len(menu_items),
        parent=aspect2d,
        #itemMakeFunction=make_context_item,
        #itemMakeExtraArgs=[self.btn_taglistItem_click, button_width]
    )

    #self.tagListItems_context.hide()
    return tagListItems_context
