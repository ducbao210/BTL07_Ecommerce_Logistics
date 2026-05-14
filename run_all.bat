@echo off
for %%f in (data\test_cases\*.csv) do (
    echo Running %%f
    logistics_app.exe "%%f"
)