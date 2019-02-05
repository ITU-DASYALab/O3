import dialog
import settings
from filedialogs import ImportFilesDialog
from objectdialogs import ObjectTagDialog
from searchdialog import SearchDialog


class DialogService:
    """
    Docstring for DialogService.
    """
    def __init__(self):
        self.open_dialog = None
        self.cellInfoDlg = None
        base.accept('dialog_closing', self.notify_close)
        base.accept('dialog_opening', self.closeInfoDialogs)


    def openDatabaseSettings(self):
        if self.open_dialog is None:
            dlg = settings.DatabaseSettingDialog()
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
            
                
    def closeInfoDialogs(self):
        if self.cellInfoDlg is not None:
            self.cellInfoDlg.close()
            self.cellInfoDlg = None


    def openCellInfoDialog(self, cellKey, numImages, cellTags=None):
        self.cellInfoDlg = dialog.CellInfoDialog(cellKey=cellKey, num_images = numImages, current_hovered_images_tags=cellTags)
        self.cellInfoDlg.draw()
    
    
    def openAddTagToObjectDialog(self, objectCubeObject):
        """docstring for openAddTagToObjectDialog"""
        if self.open_dialog is None:
            dlg = ObjectTagDialog(objectCubeObject)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
    
    
    def openImportImagesDialog(self):
        if self.open_dialog is None:
            dlg = ImportFilesDialog()
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
        
    def openAddTagFilter(self):
        if self.open_dialog is None:
            dlg = dialog.AddTagFilterDialog()
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')

    def openSearchDialog(self):
        if self.open_dialog is None:
            dlg = SearchDialog()
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')

    def openSearchDialogWithTagSet(self, tagset):
        if self.open_dialog is None:
            dlg = SearchDialog()
            self.open_dialog = dlg
            dlg.draw(tagset)
            messenger.send('dialog_opening')

    def openCreateNewTagsetDialog(self, tagset=None):
        if self.open_dialog is None:
            dlg = dialog.AddNewTagsetDialog(tagset)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')

    def openAddTagToCellDialog(self, cell):
        if self.open_dialog is None:
            dlg = dialog.DialogAddTagToCell(cell)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')    
    
    def open_add_numerical_range(self, dim):
        if self.open_dialog is None:
            dlg = dialog.DialogAddNumericalRange(dim)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
            
    def open_add_tagfilter(self, dim):
        if self.open_dialog is None:
            dlg = dialog.DialogAddTagFilter(dim)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
    
    def open_add_date_range(self, dim):
        if self.open_dialog is None:
            dlg = dialog.DialogAddDateFilter(dim)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
    
    def open_add_time_range(self, dim):
        if self.open_dialog is None:
            dlg = dialog.DialogAddTimeFilter(dim)
            self.open_dialog = dlg
            dlg.draw()
            messenger.send('dialog_opening')
    
    def open_settings(self):
        if self.open_dialog is None:
            dlg = settings.SettingsDialog()
            self.open_dialog = dlg
    
    def notify_close(self):
        self.open_dialog = None
    
    def hasOpenDialog(self):
        if self.open_dialog is None: return False
        return True 

    def searchWords(self, words):
        print 'Tokst'
        print words

# Create instance of the dialog service.
dialogService = DialogService()
