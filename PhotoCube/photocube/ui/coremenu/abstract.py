import photocube.cube
from photocube.devices import mouse_handler

class AbstractMenu:
    def __init__(self):
        self.cards = []
        self.dict_cards = dict()
        self.messages = []
        self.current_focus_card = None 
        
    def add_card_np(self, np):
        self.cards.append( np )
        
        # Make the card mouse-overable and clickable.
        self.messageHover, self.messageLeave = mouse_handler.makeNPMouseHoverable(np)
        self.messageClickRight = mouse_handler.makeNPPickableRight(np)
        self.messageClickLeft = mouse_handler.makeNPPickableLeft(np)

        base.accept(self.messageClickRight, self.on_card_click)
        base.accept(self.messageClickLeft, self.on_card_click)
        
        self.messages.append( self.messageClickRight )
        self.messages.append( self.messageClickLeft )
        
        base.accept(self.messageLeave, self.mouse_leave_card)
        base.accept(self.messageHover, self.mouse_over_card)
        
        # todo: make this more generic!
        base.accept('zoomout_none', self.clear_glow) 
            
    
    def clear_glow(self):
        if self.current_focus_card is not None:
            if not photocube.ui.coremenu.context_menu_handler.has_open_context():
                try:
                    c = self.dict_cards[self.current_focus_card]
                    c.setColor(0, 0, 0)
                    self.current_focus_card = None
                except:
                    self.current_focus_card = None
    
    
    def add_card(self, card_np, card):
        self.dict_cards[ card_np.__str__() ] = card
    
        
    def remove_cards(self):
        # Remove all messages
        for message in self.messages:
            base.ignore( message )
        
        # Remove all the card nps.
        for n in self.cards:
            n.remove()
        # Create new card dict hash.
        self.dict_cards = dict()
        
        # Create new list for card nps.
        self.cards = []
    
    
    def on_card_click(self, p):
        pass
    
    
    def mouse_leave_card(self, p):
        if not photocube.ui.coremenu.context_menu_handler.has_open_context():
            c = self.dict_cards[self.current_focus_card]
            c.setColor(0, 0, 0)
            self.current_focus_card = None

    def mouse_over_card(self, p):
        if not photocube.ui.coremenu.context_menu_handler.has_open_context():
            c = self.dict_cards[p.__str__()]
            self.current_focus_card = p.__str__()
            c.setColor(0.15, 0.15, 0.15)
    
    def reload(self):
        pass
    
    def show(self):
        pass
    
    def hide(self):
        pass
