<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.btnSend = New System.Windows.Forms.Button()
        Me.btnConnect = New System.Windows.Forms.Button()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.serialLog = New System.Windows.Forms.RichTextBox()
        Me.tbBattery = New System.Windows.Forms.TextBox()
        Me.dtpStartTime = New System.Windows.Forms.DateTimePicker()
        Me.dtpStartDate = New System.Windows.Forms.DateTimePicker()
        Me.cbDelay = New System.Windows.Forms.CheckBox()
        Me.dtpInterval = New System.Windows.Forms.DateTimePicker()
        Me.cbContinuous = New System.Windows.Forms.CheckBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.cbPorts = New System.Windows.Forms.ComboBox()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.tbSN = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.link328 = New System.Windows.Forms.LinkLabel()
        Me.cbBattery = New System.Windows.Forms.ComboBox()
        Me.tbCapacity = New System.Windows.Forms.TextBox()
        Me.lblCapacity = New System.Windows.Forms.Label()
        Me.lblBatteryConfig = New System.Windows.Forms.Label()
        Me.BatteryPanel = New System.Windows.Forms.Panel()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.linkIridium = New System.Windows.Forms.LinkLabel()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.btnHexSend = New System.Windows.Forms.Button()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.cbPressure = New System.Windows.Forms.CheckBox()
        Me.cbBackscatter = New System.Windows.Forms.CheckBox()
        Me.cbTemperature = New System.Windows.Forms.CheckBox()
        Me.cbAmbientLight = New System.Windows.Forms.CheckBox()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.Panel2 = New System.Windows.Forms.Panel()
        Me.nudCurrent = New System.Windows.Forms.NumericUpDown()
        Me.LinksPanel = New System.Windows.Forms.Panel()
        Me.DelayPanel = New System.Windows.Forms.Panel()
        Me.Panel3 = New System.Windows.Forms.Panel()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.RichTextBox2 = New System.Windows.Forms.RichTextBox()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.BatteryPanel.SuspendLayout()
        Me.Panel2.SuspendLayout()
        CType(Me.nudCurrent, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.LinksPanel.SuspendLayout()
        Me.DelayPanel.SuspendLayout()
        Me.Panel3.SuspendLayout()
        Me.SuspendLayout()
        '
        'btnSend
        '
        Me.btnSend.BackColor = System.Drawing.SystemColors.ButtonFace
        Me.btnSend.Enabled = False
        Me.btnSend.Location = New System.Drawing.Point(282, 90)
        Me.btnSend.Margin = New System.Windows.Forms.Padding(4)
        Me.btnSend.Name = "btnSend"
        Me.btnSend.Size = New System.Drawing.Size(159, 36)
        Me.btnSend.TabIndex = 0
        Me.btnSend.Text = "Send Settings"
        Me.btnSend.UseVisualStyleBackColor = False
        '
        'btnConnect
        '
        Me.btnConnect.Location = New System.Drawing.Point(161, 37)
        Me.btnConnect.Margin = New System.Windows.Forms.Padding(4)
        Me.btnConnect.Name = "btnConnect"
        Me.btnConnect.Size = New System.Drawing.Size(111, 36)
        Me.btnConnect.TabIndex = 3
        Me.btnConnect.TabStop = False
        Me.btnConnect.Text = "Connect"
        Me.btnConnect.UseVisualStyleBackColor = True
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(15, 88)
        Me.Label3.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(187, 25)
        Me.Label3.TabIndex = 10
        Me.Label3.Text = "Est. Battery Life [days]:"
        '
        'serialLog
        '
        Me.serialLog.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.serialLog.Font = New System.Drawing.Font("Courier New", 10.2!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.serialLog.Location = New System.Drawing.Point(474, 40)
        Me.serialLog.Margin = New System.Windows.Forms.Padding(4)
        Me.serialLog.Name = "serialLog"
        Me.serialLog.ReadOnly = True
        Me.serialLog.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical
        Me.serialLog.Size = New System.Drawing.Size(594, 884)
        Me.serialLog.TabIndex = 11
        Me.serialLog.Text = ""
        '
        'tbBattery
        '
        Me.tbBattery.BackColor = System.Drawing.SystemColors.ButtonFace
        Me.tbBattery.Location = New System.Drawing.Point(219, 88)
        Me.tbBattery.Margin = New System.Windows.Forms.Padding(4)
        Me.tbBattery.Name = "tbBattery"
        Me.tbBattery.ReadOnly = True
        Me.tbBattery.Size = New System.Drawing.Size(112, 31)
        Me.tbBattery.TabIndex = 13
        '
        'dtpStartTime
        '
        Me.dtpStartTime.Enabled = False
        Me.dtpStartTime.Format = System.Windows.Forms.DateTimePickerFormat.Custom
        Me.dtpStartTime.Location = New System.Drawing.Point(299, 18)
        Me.dtpStartTime.Margin = New System.Windows.Forms.Padding(4)
        Me.dtpStartTime.Name = "dtpStartTime"
        Me.dtpStartTime.ShowUpDown = True
        Me.dtpStartTime.Size = New System.Drawing.Size(96, 31)
        Me.dtpStartTime.TabIndex = 14
        '
        'dtpStartDate
        '
        Me.dtpStartDate.Enabled = False
        Me.dtpStartDate.Format = System.Windows.Forms.DateTimePickerFormat.[Short]
        Me.dtpStartDate.Location = New System.Drawing.Point(167, 19)
        Me.dtpStartDate.Margin = New System.Windows.Forms.Padding(4)
        Me.dtpStartDate.Name = "dtpStartDate"
        Me.dtpStartDate.Size = New System.Drawing.Size(120, 31)
        Me.dtpStartDate.TabIndex = 17
        '
        'cbDelay
        '
        Me.cbDelay.AutoSize = True
        Me.cbDelay.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point)
        Me.cbDelay.Location = New System.Drawing.Point(16, 25)
        Me.cbDelay.Margin = New System.Windows.Forms.Padding(4)
        Me.cbDelay.Name = "cbDelay"
        Me.cbDelay.Size = New System.Drawing.Size(135, 24)
        Me.cbDelay.TabIndex = 18
        Me.cbDelay.Text = "Delayed start"
        Me.cbDelay.UseVisualStyleBackColor = True
        '
        'dtpInterval
        '
        Me.dtpInterval.Format = System.Windows.Forms.DateTimePickerFormat.Custom
        Me.dtpInterval.Location = New System.Drawing.Point(287, 157)
        Me.dtpInterval.Margin = New System.Windows.Forms.Padding(4)
        Me.dtpInterval.Name = "dtpInterval"
        Me.dtpInterval.ShowUpDown = True
        Me.dtpInterval.Size = New System.Drawing.Size(129, 31)
        Me.dtpInterval.TabIndex = 15
        Me.dtpInterval.Value = New Date(1970, 1, 1, 0, 15, 0, 0)
        '
        'cbContinuous
        '
        Me.cbContinuous.AutoSize = True
        Me.cbContinuous.Location = New System.Drawing.Point(40, 195)
        Me.cbContinuous.Margin = New System.Windows.Forms.Padding(4)
        Me.cbContinuous.Name = "cbContinuous"
        Me.cbContinuous.Size = New System.Drawing.Size(218, 29)
        Me.cbContinuous.TabIndex = 5
        Me.cbContinuous.Text = "Continuous (max freq.)"
        Me.cbContinuous.UseVisualStyleBackColor = True
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(37, 157)
        Me.Label2.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(235, 25)
        Me.Label2.TabIndex = 9
        Me.Label2.Text = "Sample Interval [HH:mm:ss]:"
        '
        'cbPorts
        '
        Me.cbPorts.FormattingEnabled = True
        Me.cbPorts.Location = New System.Drawing.Point(37, 40)
        Me.cbPorts.Margin = New System.Windows.Forms.Padding(4)
        Me.cbPorts.Name = "cbPorts"
        Me.cbPorts.Size = New System.Drawing.Size(116, 33)
        Me.cbPorts.TabIndex = 20
        '
        'Timer1
        '
        Me.Timer1.Interval = 25
        '
        'tbSN
        '
        Me.tbSN.BackColor = System.Drawing.SystemColors.ButtonFace
        Me.tbSN.Location = New System.Drawing.Point(134, 91)
        Me.tbSN.Margin = New System.Windows.Forms.Padding(4)
        Me.tbSN.Name = "tbSN"
        Me.tbSN.ReadOnly = True
        Me.tbSN.Size = New System.Drawing.Size(88, 31)
        Me.tbSN.TabIndex = 21
        Me.tbSN.Text = "N/A"
        Me.tbSN.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(35, 95)
        Me.Label1.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(87, 25)
        Me.Label1.TabIndex = 22
        Me.Label1.Text = "Serial No."
        '
        'link328
        '
        Me.link328.AutoSize = True
        Me.link328.Location = New System.Drawing.Point(81, 9)
        Me.link328.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.link328.Name = "link328"
        Me.link328.Size = New System.Drawing.Size(127, 25)
        Me.link328.TabIndex = 24
        Me.link328.TabStop = True
        Me.link328.Text = "OpenOBS-328"
        '
        'cbBattery
        '
        Me.cbBattery.FormattingEnabled = True
        Me.cbBattery.Items.AddRange(New Object() {"2000 mAh Li-SOCL2", "800 mAh Li-ion", "Custom (3.3-5V)"})
        Me.cbBattery.Location = New System.Drawing.Point(15, 39)
        Me.cbBattery.Margin = New System.Windows.Forms.Padding(4)
        Me.cbBattery.Name = "cbBattery"
        Me.cbBattery.Size = New System.Drawing.Size(335, 33)
        Me.cbBattery.TabIndex = 27
        '
        'tbCapacity
        '
        Me.tbCapacity.Location = New System.Drawing.Point(215, 133)
        Me.tbCapacity.Margin = New System.Windows.Forms.Padding(4)
        Me.tbCapacity.Name = "tbCapacity"
        Me.tbCapacity.Size = New System.Drawing.Size(72, 31)
        Me.tbCapacity.TabIndex = 28
        Me.tbCapacity.Text = "2000"
        Me.tbCapacity.Visible = False
        '
        'lblCapacity
        '
        Me.lblCapacity.AutoSize = True
        Me.lblCapacity.Location = New System.Drawing.Point(15, 136)
        Me.lblCapacity.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.lblCapacity.Name = "lblCapacity"
        Me.lblCapacity.Size = New System.Drawing.Size(136, 25)
        Me.lblCapacity.TabIndex = 29
        Me.lblCapacity.Text = "Capacity [mAh]:"
        Me.lblCapacity.Visible = False
        '
        'lblBatteryConfig
        '
        Me.lblBatteryConfig.AutoSize = True
        Me.lblBatteryConfig.BackColor = System.Drawing.Color.Transparent
        Me.lblBatteryConfig.Location = New System.Drawing.Point(12, 10)
        Me.lblBatteryConfig.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.lblBatteryConfig.Name = "lblBatteryConfig"
        Me.lblBatteryConfig.Size = New System.Drawing.Size(178, 25)
        Me.lblBatteryConfig.TabIndex = 32
        Me.lblBatteryConfig.Text = "Battery configuration"
        '
        'BatteryPanel
        '
        Me.BatteryPanel.Controls.Add(Me.Panel1)
        Me.BatteryPanel.Controls.Add(Me.lblBatteryConfig)
        Me.BatteryPanel.Controls.Add(Me.lblCapacity)
        Me.BatteryPanel.Controls.Add(Me.cbBattery)
        Me.BatteryPanel.Controls.Add(Me.tbCapacity)
        Me.BatteryPanel.Controls.Add(Me.Label3)
        Me.BatteryPanel.Controls.Add(Me.tbBattery)
        Me.BatteryPanel.Location = New System.Drawing.Point(21, 689)
        Me.BatteryPanel.Margin = New System.Windows.Forms.Padding(4)
        Me.BatteryPanel.Name = "BatteryPanel"
        Me.BatteryPanel.Size = New System.Drawing.Size(421, 178)
        Me.BatteryPanel.TabIndex = 33
        '
        'Panel1
        '
        Me.Panel1.Location = New System.Drawing.Point(0, -245)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(426, 165)
        Me.Panel1.TabIndex = 33
        '
        'linkIridium
        '
        Me.linkIridium.AutoSize = True
        Me.linkIridium.Location = New System.Drawing.Point(230, 9)
        Me.linkIridium.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.linkIridium.Name = "linkIridium"
        Me.linkIridium.Size = New System.Drawing.Size(153, 25)
        Me.linkIridium.TabIndex = 34
        Me.linkIridium.TabStop = True
        Me.linkIridium.Text = "OpenOBS-Iridium"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(11, 9)
        Me.Label4.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(69, 25)
        Me.Label4.TabIndex = 35
        Me.Label4.Text = "Github:"
        '
        'btnHexSend
        '
        Me.btnHexSend.Location = New System.Drawing.Point(312, 37)
        Me.btnHexSend.Margin = New System.Windows.Forms.Padding(4)
        Me.btnHexSend.Name = "btnHexSend"
        Me.btnHexSend.Size = New System.Drawing.Size(130, 36)
        Me.btnHexSend.TabIndex = 36
        Me.btnHexSend.TabStop = False
        Me.btnHexSend.Text = "Upload .hex"
        Me.btnHexSend.UseVisualStyleBackColor = True
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(273, 43)
        Me.Label5.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(37, 25)
        Me.Label5.TabIndex = 37
        Me.Label5.Text = "OR"
        '
        'cbPressure
        '
        Me.cbPressure.AutoSize = True
        Me.cbPressure.BackColor = System.Drawing.Color.Transparent
        Me.cbPressure.Checked = True
        Me.cbPressure.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbPressure.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.cbPressure.Location = New System.Drawing.Point(250, 90)
        Me.cbPressure.Name = "cbPressure"
        Me.cbPressure.Size = New System.Drawing.Size(110, 29)
        Me.cbPressure.TabIndex = 39
        Me.cbPressure.Text = "Pressure"
        Me.cbPressure.UseVisualStyleBackColor = False
        '
        'cbBackscatter
        '
        Me.cbBackscatter.AutoSize = True
        Me.cbBackscatter.BackColor = System.Drawing.Color.Transparent
        Me.cbBackscatter.Checked = True
        Me.cbBackscatter.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbBackscatter.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.cbBackscatter.Location = New System.Drawing.Point(250, 55)
        Me.cbBackscatter.Name = "cbBackscatter"
        Me.cbBackscatter.Size = New System.Drawing.Size(137, 29)
        Me.cbBackscatter.TabIndex = 38
        Me.cbBackscatter.Text = "Backscatter"
        Me.cbBackscatter.UseVisualStyleBackColor = False
        '
        'cbTemperature
        '
        Me.cbTemperature.AutoSize = True
        Me.cbTemperature.BackColor = System.Drawing.Color.Transparent
        Me.cbTemperature.Checked = True
        Me.cbTemperature.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbTemperature.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.cbTemperature.Location = New System.Drawing.Point(250, 125)
        Me.cbTemperature.Name = "cbTemperature"
        Me.cbTemperature.Size = New System.Drawing.Size(146, 29)
        Me.cbTemperature.TabIndex = 40
        Me.cbTemperature.Text = "Temperature"
        Me.cbTemperature.UseVisualStyleBackColor = False
        '
        'cbAmbientLight
        '
        Me.cbAmbientLight.AutoSize = True
        Me.cbAmbientLight.BackColor = System.Drawing.Color.Transparent
        Me.cbAmbientLight.Checked = True
        Me.cbAmbientLight.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbAmbientLight.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.cbAmbientLight.Location = New System.Drawing.Point(250, 20)
        Me.cbAmbientLight.Name = "cbAmbientLight"
        Me.cbAmbientLight.Size = New System.Drawing.Size(159, 29)
        Me.cbAmbientLight.TabIndex = 41
        Me.cbAmbientLight.Text = "Ambient Light"
        Me.cbAmbientLight.UseVisualStyleBackColor = False
        '
        'RichTextBox1
        '
        Me.RichTextBox1.BackColor = System.Drawing.SystemColors.GradientInactiveCaption
        Me.RichTextBox1.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.RichTextBox1.Location = New System.Drawing.Point(5, 9)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None
        Me.RichTextBox1.Size = New System.Drawing.Size(239, 160)
        Me.RichTextBox1.TabIndex = 42
        Me.RichTextBox1.Text = "Uncheck any measurements you do not want. This is primarily useful for the 'Conti" &
    "nuous' mode, where removing measurements can increase the frequency."
        '
        'Panel2
        '
        Me.Panel2.BackColor = System.Drawing.SystemColors.GradientInactiveCaption
        Me.Panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Panel2.Controls.Add(Me.RichTextBox1)
        Me.Panel2.Controls.Add(Me.cbAmbientLight)
        Me.Panel2.Controls.Add(Me.cbTemperature)
        Me.Panel2.Controls.Add(Me.cbBackscatter)
        Me.Panel2.Controls.Add(Me.cbPressure)
        Me.Panel2.Location = New System.Drawing.Point(21, 251)
        Me.Panel2.Name = "Panel2"
        Me.Panel2.Size = New System.Drawing.Size(429, 175)
        Me.Panel2.TabIndex = 42
        '
        'nudCurrent
        '
        Me.nudCurrent.Increment = New Decimal(New Integer() {10, 0, 0, 0})
        Me.nudCurrent.Location = New System.Drawing.Point(289, 37)
        Me.nudCurrent.Maximum = New Decimal(New Integer() {200, 0, 0, 0})
        Me.nudCurrent.Minimum = New Decimal(New Integer() {10, 0, 0, 0})
        Me.nudCurrent.Name = "nudCurrent"
        Me.nudCurrent.Size = New System.Drawing.Size(79, 31)
        Me.nudCurrent.TabIndex = 44
        Me.nudCurrent.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        Me.nudCurrent.Value = New Decimal(New Integer() {50, 0, 0, 0})
        '
        'LinksPanel
        '
        Me.LinksPanel.Controls.Add(Me.Label4)
        Me.LinksPanel.Controls.Add(Me.link328)
        Me.LinksPanel.Controls.Add(Me.linkIridium)
        Me.LinksPanel.Location = New System.Drawing.Point(21, 874)
        Me.LinksPanel.Name = "LinksPanel"
        Me.LinksPanel.Size = New System.Drawing.Size(421, 50)
        Me.LinksPanel.TabIndex = 34
        '
        'DelayPanel
        '
        Me.DelayPanel.Controls.Add(Me.cbDelay)
        Me.DelayPanel.Controls.Add(Me.dtpStartDate)
        Me.DelayPanel.Controls.Add(Me.dtpStartTime)
        Me.DelayPanel.Location = New System.Drawing.Point(21, 606)
        Me.DelayPanel.Name = "DelayPanel"
        Me.DelayPanel.Size = New System.Drawing.Size(421, 63)
        Me.DelayPanel.TabIndex = 45
        '
        'Panel3
        '
        Me.Panel3.BackColor = System.Drawing.Color.SandyBrown
        Me.Panel3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Panel3.Controls.Add(Me.Label8)
        Me.Panel3.Controls.Add(Me.Label7)
        Me.Panel3.Controls.Add(Me.RichTextBox2)
        Me.Panel3.Controls.Add(Me.Label6)
        Me.Panel3.Controls.Add(Me.nudCurrent)
        Me.Panel3.Location = New System.Drawing.Point(21, 441)
        Me.Panel3.Name = "Panel3"
        Me.Panel3.Size = New System.Drawing.Size(428, 141)
        Me.Panel3.TabIndex = 43
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.BackColor = System.Drawing.Color.Transparent
        Me.Label8.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.Label8.Location = New System.Drawing.Point(285, 71)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(93, 25)
        Me.Label8.TabIndex = 47
        Me.Label8.Text = "[10 - 200]"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.BackColor = System.Drawing.Color.Transparent
        Me.Label7.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.Label7.Location = New System.Drawing.Point(375, 43)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(41, 25)
        Me.Label7.TabIndex = 46
        Me.Label7.Text = "mA"
        '
        'RichTextBox2
        '
        Me.RichTextBox2.BackColor = System.Drawing.Color.SandyBrown
        Me.RichTextBox2.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.RichTextBox2.Location = New System.Drawing.Point(6, 6)
        Me.RichTextBox2.Name = "RichTextBox2"
        Me.RichTextBox2.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None
        Me.RichTextBox2.Size = New System.Drawing.Size(266, 131)
        Me.RichTextBox2.TabIndex = 43
        Me.RichTextBox2.Text = "The current of the infrared emitter for backscatter measurements. Must match your" &
    " calibration. Increasing this may help with low concentrations."
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.BackColor = System.Drawing.Color.Transparent
        Me.Label6.Font = New System.Drawing.Font("Segoe UI", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.Label6.Location = New System.Drawing.Point(292, 9)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(113, 25)
        Me.Label6.TabIndex = 45
        Me.Label6.Text = "LED Current"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(10.0!, 25.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.ButtonFace
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom
        Me.ClientSize = New System.Drawing.Size(1087, 936)
        Me.Controls.Add(Me.Panel3)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.btnHexSend)
        Me.Controls.Add(Me.BatteryPanel)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.tbSN)
        Me.Controls.Add(Me.cbPorts)
        Me.Controls.Add(Me.dtpInterval)
        Me.Controls.Add(Me.serialLog)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.cbContinuous)
        Me.Controls.Add(Me.btnConnect)
        Me.Controls.Add(Me.btnSend)
        Me.Controls.Add(Me.Panel2)
        Me.Controls.Add(Me.LinksPanel)
        Me.Controls.Add(Me.DelayPanel)
        Me.DoubleBuffered = True
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.Name = "Form1"
        Me.Text = "OpenOBS-328"
        Me.BatteryPanel.ResumeLayout(False)
        Me.BatteryPanel.PerformLayout()
        Me.Panel2.ResumeLayout(False)
        Me.Panel2.PerformLayout()
        CType(Me.nudCurrent, System.ComponentModel.ISupportInitialize).EndInit()
        Me.LinksPanel.ResumeLayout(False)
        Me.LinksPanel.PerformLayout()
        Me.DelayPanel.ResumeLayout(False)
        Me.DelayPanel.PerformLayout()
        Me.Panel3.ResumeLayout(False)
        Me.Panel3.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents btnSend As Button
    Friend WithEvents btnConnect As Button
    Friend WithEvents Label3 As Label
    Friend WithEvents serialLog As RichTextBox
    Friend WithEvents tbBattery As TextBox
    Friend WithEvents dtpStartTime As DateTimePicker
    Friend WithEvents dtpStartDate As DateTimePicker
    Friend WithEvents cbDelay As CheckBox
    Friend WithEvents dtpInterval As DateTimePicker
    Friend WithEvents cbContinuous As CheckBox
    Friend WithEvents Label2 As Label
    Friend WithEvents cbPorts As ComboBox
    Friend WithEvents Timer1 As Timer
    Friend WithEvents tbSN As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents link_328 As LinkLabel
    Friend WithEvents cbBattery As ComboBox
    Friend WithEvents tbCapacity As TextBox
    Friend WithEvents lblCapacity As Label
    Friend WithEvents lblBatteryConfig As Label
    Friend WithEvents BatteryPanel As Panel
    Friend WithEvents linkIridium As LinkLabel
    Friend WithEvents link328 As LinkLabel
    Friend WithEvents Label4 As Label
    Friend WithEvents btnHexSend As Button
    Friend WithEvents Label5 As Label
    Friend WithEvents Panel1 As Panel
    Friend WithEvents cbPressure As CheckBox
    Friend WithEvents cbBackscatter As CheckBox
    Friend WithEvents cbTemperature As CheckBox
    Friend WithEvents cbAmbientLight As CheckBox
    Friend WithEvents RichTextBox1 As RichTextBox
    Friend WithEvents Panel2 As Panel
    Friend WithEvents nudCurrent As NumericUpDown
    Friend WithEvents LinksPanel As Panel
    Friend WithEvents DelayPanel As Panel
    Friend WithEvents Panel3 As Panel
    Friend WithEvents RichTextBox2 As RichTextBox
    Friend WithEvents Label6 As Label
    Friend WithEvents Label7 As Label
    Friend WithEvents Label8 As Label
End Class
